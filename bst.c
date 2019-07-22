/*
 * File: bst.c
 * -----------
 * This file implements the bst.h interface, which provides a
 * general implementation of binary search trees.
 */

#include <stdio.h>
#include "genlib.h"
#include "cmpfn.h"
#include "bst.h"

/*
 * Type: treeT
 * -----------
 * Because the implementation does not know the structure of a
 * node, pointers to nodes cannot be defined explicitly and must
 * be represented using void *.  For readability, the code declares
 * any void * pointers that are in fact trees to be of type treeT.
 */

typedef void *treeT;

/*
 * Type: bstCDT
 * ------------
 * This type is the concrete type used to represent the bstADT.
 */

struct bstCDT {
    treeT root;
    int userSize, totalSize;
    cmpFnT cmpFn;
    nodeInitFnT nodeInitFn;
};

/*
 * Type: bstDataT
 * --------------
 * This record is allocated at the end of the client's structure
 * and is used to maintain the structure of the tree.  The code
 * calls BSTData on the node pointer to derive this address.
 */

typedef struct {
    treeT left, right;
} bstDataT;

/* Private function prototypes */

static treeT *RecFindNode(bstADT bst, treeT t, void *kp);
static void *RecInsertNode(bstADT bst, treeT *tptr, void *kp,
                           void *clientData);
static void *RecDeleteNode(bstADT bst, treeT *tptr, void *kp);
static void *DeleteTargetNode(bstADT bst, treeT *tptr);
static void RecMapBST(nodeFnT fn, bstADT bst, treeT t,
                      traversalOrderT order, void *clientData);
static bstDataT *BSTData(bstADT bst, treeT t);

/* Exported entries */

bstADT NewBST(int size, cmpFnT cmpFn, nodeInitFnT nodeInitFn)
{
    bstADT bst;

    bst = New(bstADT);
    bst->root = NULL;
    bst->userSize = size;
    bst->totalSize = bst->userSize + sizeof(bstDataT);
    bst->cmpFn = cmpFn;
    bst->nodeInitFn = nodeInitFn;
    return (bst);
}

void FreeBST(bstADT bst, nodeFnT freeNodeFn)
{
    MapBST(freeNodeFn, bst, PostOrder, NULL);
    FreeBlock(bst);
}

/*
 * Implementation notes: FindBSTNode, RecFindNode
 * ----------------------------------------------
 * The FindBSTNode function simply calls RecFindNode to do
 * the work.  The recursive function takes the address of
 * the current node along with the original arguments.
 */

void *FindBSTNode(bstADT bst, void *kp)
{
    return (RecFindNode(bst, bst->root, kp));
}

static treeT *RecFindNode(bstADT bst, treeT t, void *kp)
{
    bstDataT *dp;
    int sign;

    if (t == NULL) return (NULL);
    sign = bst->cmpFn(kp, t);
    if (sign == 0) return (t);
    dp = BSTData(bst, t);
    if (sign < 0) {
        return (RecFindNode(bst, dp->left, kp));
    } else {
        return (RecFindNode(bst, dp->right, kp));
    }
}

/*
 * Implementation notes: InsertBSTNode, RecInsertNode
 * --------------------------------------------------
 * The InsertBSTNode function is implemented as a simple wrapper
 * to RecInsertNode, which does all the work.  The difference
 * between the prototypes is that RecInsertNode takes a pointer
 * to the root of the current subtree as an extra argument.
 */

void *InsertBSTNode(bstADT bst, void *kp, void *clientData)
{
    return (RecInsertNode(bst, &bst->root, kp, clientData));
}

static void *RecInsertNode(bstADT bst, treeT *tptr, void *kp,
                           void *clientData)
{
    bstDataT *dp;
    treeT t;
    int sign;

    t = *tptr;
    if (t == NULL) {
        t = GetBlock(bst->totalSize);
        bst->nodeInitFn(t, kp, clientData);
        dp = BSTData(bst, t);
        dp->left = dp->right = NULL;
        *tptr = t;
        return (t);
    }
    sign = bst->cmpFn(kp, t);
    if (sign == 0) return (t);
    dp = BSTData(bst, t);
    if (sign < 0) {
        return (RecInsertNode(bst, &dp->left, kp, clientData));
    } else {
        return (RecInsertNode(bst, &dp->right, kp, clientData));
    }
}

/*
 * Implementation notes: DeleteBSTNode, RecDeleteNode
 * --------------------------------------------------
 * The first step in deleting a node is to find it using binary
 * search, which is performed by these two functions.  If the
 * node is found, DeleteTargetNode does the actual deletion.
 */

void *DeleteBSTNode(bstADT bst, void *kp)
{
    return (RecDeleteNode(bst, &bst->root, kp));
}

static void *RecDeleteNode(bstADT bst, treeT *tptr, void *kp)
{
    bstDataT *dp;
    treeT t;
    int sign;

    t = *tptr;
    if (t == NULL) return (NULL);
    sign = bst->cmpFn(kp, t);
    if (sign == 0) {
        return (DeleteTargetNode(bst, tptr));
    }
    dp = BSTData(bst, t);
    if (sign < 0) {
        return (RecDeleteNode(bst, &dp->left, kp));
    } else {
        return (RecDeleteNode(bst, &dp->right, kp));
    }
}

/*
 * Implementation notes: DeleteTargetNode
 * --------------------------------------
 * This function deletes the node whose address is passed by
 * reference in tptr.  The easy case occurs when either of the
 * children is NULL; all you need to do is replace the node with
 * its non-NULL child.  If both children are non-NULL, this code
 * finds the rightmost descendent of the left child; this node
 * may not be a leaf, but will have no right child.  Its left
 * child replaces it in the tree, after which the replacement
 * node is moved to the position occupied by the target node.
 */

static void *DeleteTargetNode(bstADT bst, treeT *tptr)
{
    treeT target, *rptr;
    bstDataT *tdp, *rdp;

    target = *tptr;
    tdp = BSTData(bst, target);
    if (tdp->left == NULL) {
        *tptr = tdp->right;
    } else if (tdp->right == NULL) {
        *tptr = tdp->left;
    } else {
        rptr = &tdp->left;
        rdp = BSTData(bst, *rptr);
        while (rdp->right != NULL) {
            rptr = &rdp->right;
            rdp = BSTData(bst, *rptr);
        }
        *tptr = *rptr;
        *rptr = rdp->left;
        rdp->left = tdp->left;
        rdp->right = tdp->right;
    }
    return (target);
}

/*
 * Implementation notes: MapBST, RecMapBST
 * ---------------------------------------
 * The MapBST function is implemented as a wrapper to the
 * recursive function RecMapBST, which does the actual work.
 */

void MapBST(nodeFnT fn, bstADT bst, traversalOrderT order,
            void *clientData)
{
    RecMapBST(fn, bst, bst->root, order, clientData);
}

static void RecMapBST(nodeFnT fn, bstADT bst, treeT t,
                      traversalOrderT order, void *clientData)
{
    bstDataT *dp;

    if (t != NULL) {
        dp = BSTData(bst, t);
        if (order == PreOrder) fn(t, clientData);
        RecMapBST(fn, bst, dp->left, order, clientData);
        if (order == InOrder) fn(t, clientData);
        RecMapBST(fn, bst, dp->right, order, clientData);
        if (order == PostOrder) fn(t, clientData);
    }
}

/* Low-level functions */

void *BSTRoot(bstADT bst)
{
    return (bst->root);
}

void *BSTLeftChild(bstADT bst, void *np)
{
    bstDataT *dp;

    if (np == NULL) Error("BSTLeftChild: Argument is NULL");
    dp = BSTData(bst, np);
    return (dp->left);
}

void *BSTRightChild(bstADT bst, void *np)
{
    bstDataT *dp;

    if (np == NULL) Error("BSTRightChild: Argument is NULL");
    dp = BSTData(bst, np);
    return (dp->right);
}

/*
 * Function: BSTData
 * Usage: dp = BSTData(bst, t);
 * ----------------------------
 * This function determines the address of the data record
 * containing the pointers for the binary tree.  This record
 * appears at the end of the user structure that begins at t.
 */

static bstDataT *BSTData(bstADT bst, treeT t)
{
    return ((bstDataT *) ((char *) t + bst->userSize));
}


