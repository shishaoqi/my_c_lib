/*
 * File: bst.c
 * -----------
 * This file implements the bst.h interface, which provides a
 * general implementation of binary search tree
 */

#include <stdio.h>
#include "genlib.h"
#include "cmpfn.h"
#include "blt.h"

/*
 * Type: treeT
 * ------------
 * Because the implementation does not know the structure of a
 * node, ponters to nodes cannot be defined explicitly and must
 * be represented using void *. For readability, the code declarees
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

typedef struct {
    int bf;
    ssize_t height;
    treeT left, right;
} bstDataT;

#define Max(a, b) ((a) > (b) ? (a) : (b))

/* Private function prototypes */
static treeT RecFindNode(bstADT bst, treeT t, void *kp);
static int RecInsertNode(bstADT bst, treeT *tptr, void *kp, void *clientData);
static void *RecDeleteNode(bstADT bst, treeT *tptr, void *kp);
static void *DeleteTargetNode(bstADT bst, treeT *tptr);
static void RecMapBST(nodeFnT fn, bstADT bst, treeT t, OrderT order, void *clientData);
static bstDataT *BSTData(bstADT bst, treeT t);
static void FixLeftImbalance(bstADT bst, treeT *tptr);
static void FixRightImbalance(bstADT bst, treeT *tptr);
static void RotateLeft(bstADT bst, treeT *tptr);
static void RotateRight(bstADT bst, treeT *tptr);
static int RecRight(bstADT bst, bstDataT *tdp, treeT *rptr, treeT *tptr);
static ssize_t GetHeight(bstADT bst, treeT t);



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
    return bst;
}

void FreeBST(bstADT bst, nodeFnT freeNodeFn)
{
    MapBST(freeNodeFn, bst, PostOrder, NULL);
    FreeBlock(bst);
}

void *FindBSTNode(bstADT bst, void *kp)
{
    return ( RecFindNode(bst, bst->root, kp) );
}

static treeT RecFindNode(bstADT bst, treeT t, void *kp)
{
    bstDataT *dp;
    int sign;

    if (t == NULL)  return NULL;
    sign = bst->cmpFn(kp, t);
    if (sign == 0)  return t;
    dp = BSTData(bst, t);
    if (sign < 0) {
        return ( RecFindNode(bst, dp->left, kp) );
    } else {
        return ( RecFindNode(bst, dp->right, kp) );
    }
}

int InsertBSTNode(bstADT bst, void *kp, void *clientData)
{
    return (RecInsertNode(bst, &bst->root, kp, clientData));
}

static int RecInsertNode(bstADT bst, treeT *tptr, void *kp, void *clientData)
{
    bstDataT lchild, rchild, *dp;
    treeT t;
    int sign, delta;

    t = *tptr;
    if (t == NULL) {
        t = GetBlock(bst->totalSize);
        bst->nodeInitFn(t, kp, clientData);
        dp = BSTData(bst, t);
        dp->bf = 0;
        // TODO
        dp->height = 0;
        dp->left = dp->right = NULL;
        *tptr = t;
        return 1;
    }

    sign = bst->cmpFn(kp, t);

    if (sign == 0) return 0;

    dp = BSTData(bst, t);
    if (sign < 0 ) {
        delta = RecInsertNode(bst, &dp->left, kp, clientData);
        if (delta == 0) return 0;
        dp->height = Max(GetHeight(bst, dp->left), GetHeight(bst, dp->right)) + 1;
        switch (dp->bf) {
            case 1: dp->bf = 0; return 0;
            case 0: dp->bf = -1; return 1;
            case -1: FixLeftImbalance (bst, tptr); return 0;
        }
    } else {
        delta = RecInsertNode(bst, &dp->right, kp, clientData);
        if (delta == 0) return 0;
        dp->height = Max(GetHeight(bst, dp->left), GetHeight(bst, dp->right)) + 1;
        switch (dp->bf) {
            case -1: dp->bf = 0; return 0;
            case 0:  dp->bf = 1; return 1;
            case 1:  FixRightImbalance (bst, tptr); return 0;
        }
    }
}

void *DeleteBSTNode(bstADT bst, void *kp)
{
    return RecDeleteNode(bst, &bst->root, kp);
}

static void *RecDeleteNode(bstADT bst, treeT *tptr, void *kp)
{
    bstDataT *dp, *cdp, *lcdp, *rcdp;
    treeT target, newTarget, ctr;
    int sign, height, delta;

    target = *tptr;
    if (target == NULL) {
        return 0;
    }

    sign = bst->cmpFn(kp, target);
    dp = BSTData(bst, target);
    if (sign == 0) {
        target = (DeleteTargetNode(bst, tptr));
    } else if (sign < 0) {
        target = RecDeleteNode(bst, &dp->left, kp);
    } else if (sign > 0) {
        target = RecDeleteNode(bst, &dp->right, kp); 
    }

    //dp->bf = GetHeight(bst, dp->right) - GetHeight(bst, dp->left) + 1;
    dp->height = Max(GetHeight(bst, dp->left), GetHeight(bst, dp->right)) + 1;

    ssize_t heightDelta = GetHeight(bst, dp->left) - GetHeight(bst, dp->right);
    if(heightDelta == 2){
        lcdp = BSTData(bst, dp->left);
        if(GetHeight(bst, lcdp->left) >= GetHeight(bst, lcdp->right))
            FixLeftImbalance(bst, tptr);
        else
            FixLeftImbalance(bst, tptr);
    }else if(heightDelta == -2){
        rcdp = BSTData(bst, dp->right);
        if(GetHeight(bst, rcdp->left) >= GetHeight(bst, rcdp->right))
            FixRightImbalance(bst, tptr);
        else
            FixRightImbalance(bst, tptr);
    }

    return target;
}

static void *DeleteTargetNode(bstADT bst, treeT *tptr)
{
    treeT target, cptr;
    bstDataT *tdp, *cdp;

    target = *tptr;
    tdp = BSTData(bst, target);

    if (tdp->left == NULL) {
        *tptr = tdp->right;
    } else if (tdp->right == NULL) {
        *tptr = tdp->left;
    } else {
        cptr = tdp->left;
        cdp = BSTData(bst, cptr);
        while (cdp->right != NULL) {
            cptr = cdp->right;
            cdp = BSTData(bst, cptr);
        }

        *tptr = cptr;
        //cptr = cdp->left;
        RecDeleteNode(bst, &tdp->left, cptr);
        cdp->bf = tdp->bf;
        //cdp->height = tdp->height;
        cdp->height = Max(GetHeight(bst, tdp->left), GetHeight(bst, tdp->right)) + 1;
        cdp->left = tdp->left;
        cdp->right = tdp->right;
    }

    return target;
}

static void FixLeftImbalance(bstADT bst, treeT *tptr)
{
    treeT t, parent, child, *cptr;
    bstDataT *pdp, *cdp;
    int oldBF;

    parent = *tptr;
    pdp = BSTData(bst, parent);
    cptr = &pdp->left;
    child = pdp->left;
    cdp = BSTData(bst, child);
    if (cdp->bf != pdp->bf) {
        cdp = BSTData(bst, cdp->right);
        oldBF = cdp->bf;
        RotateLeft(bst, cptr);
        RotateRight(bst, tptr);
        t = *tptr;
        pdp = BSTData(bst, t);
        pdp->bf = 0;
        switch (oldBF) {
        case -1: {
            cdp = BSTData(bst, pdp->left);  cdp->bf = 0;
            cdp = BSTData(bst, pdp->right); cdp->bf = 1; break;
        }
        case  0: {
            cdp = BSTData(bst, pdp->left);  cdp->bf = 0;
            cdp = BSTData(bst, pdp->right);  cdp->bf = 0; break;
        }
        case  1: {
            cdp = BSTData(bst, pdp->left);   cdp->bf = -1;
            cdp = BSTData(bst, pdp->right);  cdp->bf = 0; break;
        }
        }
    } else {
        RotateRight(bst, tptr);
        t = *tptr;
        pdp = BSTData(bst, t);
        cdp = BSTData(bst, pdp->right);
        pdp->bf = cdp->bf = 0;
    }
}

static void FixRightImbalance(bstADT bst, treeT *tptr)
{
    treeT t, parent, child, *cptr;
    bstDataT *pdp, *cdp;
    int oldBF;

    parent = *tptr;
    pdp = BSTData(bst, parent);
    cptr = &pdp->right;
    child = pdp->right;
    cdp = BSTData(bst, child);
    if (cdp->bf != pdp->bf) {
        cdp = BSTData(bst, cdp->left);
        oldBF = cdp->bf;
        RotateRight(bst, cptr);
        RotateLeft(bst, tptr);
        t = *tptr;
        pdp = BSTData(bst, t);
        pdp->bf = 0;
        switch (oldBF) {
        case -1: {
            cdp = BSTData(bst, pdp->left);  cdp->bf = 0;
            cdp = BSTData(bst, pdp->right); cdp->bf = 1; break;
        }
        case  0: {
            cdp = BSTData(bst, pdp->left);  cdp->bf = 0;
            cdp = BSTData(bst, pdp->right); cdp->bf = 0; break;
        }
        case  1: {
            cdp = BSTData(bst, pdp->left);   cdp->bf = -1;
            cdp = BSTData(bst, pdp->right);  cdp->bf = 0; break;
        }
        }
    } else {
        RotateLeft(bst, tptr);
        t = *tptr;
        pdp = BSTData(bst, t);
        cdp = BSTData(bst, pdp->left);
        cdp->bf = pdp->bf = 0;
    }
}

/*  rotates to the left (p: parent , c: child)
         p                  c
        / \                / \
       X   c    ======    p   Z
          / \            / \
         Y   Z          X   Y
 */
static void RotateLeft(bstADT bst, treeT *tptr)
{
    treeT parent, child, lchild, rchild;
    bstDataT *pdp, *cdp;

    parent = *tptr;
    pdp = BSTData(bst, parent);
    child = pdp->right;
    cdp = BSTData(bst, child);
    pdp->right = cdp->left;
    cdp->left = parent;
    (*tptr) = child;

    pdp->height = Max(GetHeight(bst, pdp->left), GetHeight(bst, pdp->right)) + 1;
    cdp->height = Max(GetHeight(bst, cdp->left), GetHeight(bst, cdp->right)) + 1;
}

/*  rotates to the right (p: parent , c: child)
         p                  c
        / \                / \
       c   Z    ======    X   p
      / \                    / \
     X   Y                  Y   Z
 */
static void RotateRight(bstADT bst, treeT *tptr)
{
    treeT parent, child, lchild, rchild;
    bstDataT *pdp, *cdp;

    parent = *tptr;
    pdp = BSTData(bst, parent);
    child = pdp->left;
    cdp = BSTData(bst, child);
    pdp->left = cdp->right;
    cdp->right = parent;
    (*tptr) = child;

    pdp->height = Max(GetHeight(bst, pdp->left), GetHeight(bst, pdp->right)) + 1;
    cdp->height = Max(GetHeight(bst, cdp->left), GetHeight(bst, cdp->right)) + 1;
}

void MapBST(nodeFnT fn, bstADT bst, OrderT order, void *clientData)
{
    RecMapBST(fn, bst, bst->root, order, clientData);
}

static void RecMapBST(nodeFnT fn, bstADT bst, treeT t, OrderT order, void *clientData)
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

static bstDataT *BSTData(bstADT bst, treeT t)
{
    return  (bstDataT *) ((char *)t + bst->userSize );
}

static ssize_t GetHeight(bstADT bst, treeT t)
{
    bstDataT *dp;
    if (t == NULL)  return -1;

    dp = BSTData(bst, t);
    return dp->height;
}
