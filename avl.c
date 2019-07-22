/*
* @Author: shishao
* @Date:   2019-07-19 18:10:06
* @Last Modified by:   shishao
* @Last Modified time: 2019-07-23 00:53:00
*/

/*
 * File: avl.c
 * -----------
 * This file implements the avl.h interface, which provides a
 * general implementation of binary search tree
 */

#include <stdio.h>
#include "genlib.h"
#include "cmpfn.h"
#include "avl.h"

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
 * Type: avlCDT
 * ------------
 * This type is the concrete type used to represent the avlADT.
 */
struct avlCDT {
    treeT root;
    int userSize, totalSize;
    cmpFnT cmpFn;
    nodeInitFnT nodeInitFn;
};

typedef struct {
    int height; //ssize_t fail 
    treeT left, right;
} avlDataT;

#define Max(a, b) ((a) > (b) ? (a) : (b))

/* Private function prototypes */
static treeT RecFindNode(avlADT avl, treeT t, void *kp);
static int RecInsertNode(avlADT avl, treeT *tptr, void *kp, void *clientData);
static void *RecDeleteNode(avlADT avl, treeT *tptr, void *kp);
static void *DeleteTargetNode(avlADT avl, treeT *tptr);
static void RecMapAVL(nodeFnT fn, avlADT avl, treeT t, traversalOrderT order, void *clientData);
static avlDataT *AVLData(avlADT avl, treeT t);
static void RotateLeft(avlADT avl, treeT *tptr);
static void RotateRight(avlADT avl, treeT *tptr);
static void LeftRightRotate(avlADT avl, treeT *tptr);
static void RightLeftRotate(avlADT avl, treeT *tptr);
static int GetHeight(avlADT avl, treeT t);

/* Exported entries */

avlADT NewAVL(int size, cmpFnT cmpFn, nodeInitFnT nodeInitFn)
{
    avlADT avl;

    avl = New(avlADT);
    avl->root = NULL;
    avl->userSize = size;
    avl->totalSize = avl->userSize + sizeof(avlDataT);
    avl->cmpFn = cmpFn;
    avl->nodeInitFn = nodeInitFn;
    return avl;
}

void FreeAVL(avlADT avl, nodeFnT freeNodeFn)
{
    MapAVL(freeNodeFn, avl, PostOrder, NULL);
    FreeBlock(avl);
}

void *FindAVLNode(avlADT avl, void *kp)
{
    return ( RecFindNode(avl, avl->root, kp) );
}

static treeT RecFindNode(avlADT avl, treeT t, void *kp)
{
    avlDataT *dp;
    int sign;

    if (t == NULL)  return NULL;
    sign = avl->cmpFn(kp, t);
    if (sign == 0)  return t;
    dp = AVLData(avl, t);
    if (sign < 0) {
        return ( RecFindNode(avl, dp->left, kp) );
    } else {
        return ( RecFindNode(avl, dp->right, kp) );
    }
}

int InsertAVLNode(avlADT avl, void *kp, void *clientData)
{
    return (RecInsertNode(avl, &avl->root, kp, clientData));
}

static int RecInsertNode(avlADT avl, treeT *tptr, void *kp, void *clientData)
{
    avlDataT *dp;
    treeT t;
    int sign;

    t = *tptr;
    if (t == NULL) {
        t = GetBlock(avl->totalSize);
        avl->nodeInitFn(t, kp, clientData);
        dp = AVLData(avl, t);
        dp->height = 0;
        dp->left = dp->right = NULL;
        *tptr = t;
        return 1;
    }

    sign = avl->cmpFn(kp, t);

    if (sign == 0) return 0;

    dp = AVLData(avl, t);
    if (sign < 0 ) {
        RecInsertNode(avl, &dp->left, kp, clientData);
    } else {
        RecInsertNode(avl, &dp->right, kp, clientData);
    }
    dp->height = Max(GetHeight(avl, dp->left), GetHeight(avl, dp->right)) + 1;

    int heightDelta = GetHeight(avl, dp->left) - GetHeight(avl, dp->right);

    if(heightDelta == 2){
        if(avl->cmpFn(kp, dp->left) < 0)
            RotateRight(avl, tptr);
        else
            LeftRightRotate(avl, tptr);
    }else if(heightDelta == -2){
        if(avl->cmpFn(kp, dp->right) < 0)
            RightLeftRotate(avl, tptr);
        else
            RotateLeft(avl, tptr);
    }
}

void *DeleteAVLNode(avlADT avl, void *kp)
{
    return RecDeleteNode(avl, &avl->root, kp);
}

static void *RecDeleteNode(avlADT avl, treeT *tptr, void *kp)
{
    avlDataT *dp, *lcdp, *rcdp;
    treeT target;
    int sign;

    target = *tptr;
    if (target == NULL) {
        return NULL;
    }

    sign = avl->cmpFn(kp, target);
    dp = AVLData(avl, target);
    if (sign == 0){
        DeleteTargetNode(avl, tptr);
    } else if (sign < 0) {
        RecDeleteNode(avl, &dp->left, kp);
    } else if (sign > 0) {
        RecDeleteNode(avl, &dp->right, kp);
    }
    dp->height = Max(GetHeight(avl, dp->left), GetHeight(avl, dp->right)) + 1;

    int heightDelta = GetHeight(avl, dp->left) - GetHeight(avl, dp->right);
    if(heightDelta == 2){
        lcdp = AVLData(avl, dp->left);
        if(GetHeight(avl, lcdp->left) >= GetHeight(avl, lcdp->right))
            RotateRight(avl, tptr);
        else
            LeftRightRotate(avl, tptr);
    }else if(heightDelta == -2){
        rcdp = AVLData(avl, dp->right);
        if(GetHeight(avl, rcdp->right) >= GetHeight(avl, rcdp->left))
            RotateLeft(avl, tptr);
        else
            RightLeftRotate(avl, tptr);
    }

    return target;
}

static void *DeleteTargetNode(avlADT avl, treeT *tptr)
{
    treeT target, cptr, newTarget;
    avlDataT *tdp, *cdp;
    avlDataT *lcdp, *rcdp;

    target = *tptr;
    tdp = AVLData(avl, target);

    if (tdp->left == NULL) {
        *tptr = tdp->right;
        return NULL;
    } else if (tdp->right == NULL) {
        *tptr = tdp->left;
        return NULL;
    } else {
        cptr = tdp->left;
        cdp = AVLData(avl, cptr);
        while (cdp->right != NULL) {
            cptr = cdp->right;
            cdp = AVLData(avl, cptr);
        }

        *tptr = cptr;
        //cptr = cdp->left;
        newTarget = RecDeleteNode(avl, &tdp->left, cptr);
        //cdp->height = tdp->height;//此注释掉的，经测试不正确（下面的才能正常执行）
        cdp->height = Max(GetHeight(avl, tdp->left), GetHeight(avl, tdp->right)) + 1;
        cdp->left = tdp->left;
        cdp->right = tdp->right;

        //此注释掉的，经测试不能加上。（网上的参照不对吧）
        //将 target 看做根结点，删除的元素在左子树，此时判断左子树与右子树的高度差是不是>=2
        /*int heightDelta = GetHeight(avl, tdp->left) - GetHeight(avl, tdp->right);
        if(heightDelta == 2){
            lcdp = AVLData(avl, tdp->left);
            if(GetHeight(avl, lcdp->left) >= GetHeight(avl, lcdp->right))
                RotateRight(avl, tptr);
            else
                LeftRightRotate(avl, tptr);
        }else if(heightDelta == -2){
            rcdp = AVLData(avl, tdp->right);
            if(GetHeight(avl, rcdp->right) >= GetHeight(avl, rcdp->left))
                RotateLeft(avl, tptr);
            else
                RightLeftRotate(avl, tptr);
        }*/
    }

    return tptr;
}

static void LeftRightRotate(avlADT avl, treeT *tptr) {
    avlDataT *pdp;
    treeT parent, *cptr;

    parent = *tptr;
    pdp = AVLData(avl, parent);
    cptr = &pdp->left;
    
    RotateLeft(avl, cptr);
    RotateRight(avl, tptr);
}

static void RightLeftRotate(avlADT avl, treeT *tptr) {
    avlDataT *pdp;
    treeT parent, *cptr;

    parent = *tptr;
    pdp = AVLData(avl, parent);
    cptr = &pdp->right;

    RotateRight(avl, cptr);
    RotateLeft(avl, tptr);
}


/*  rotates to the left (p: parent , c: child)
         p                  c
        / \                / \
       X   c    ======    p   Z
          / \            / \
         Y   Z          X   Y
 */
static void RotateLeft(avlADT avl, treeT *tptr)
{
    treeT parent, child;
    avlDataT *pdp, *cdp;

    parent = *tptr;
    pdp = AVLData(avl, parent);
    child = pdp->right;
    cdp = AVLData(avl, child);
    pdp->right = cdp->left;
    cdp->left = parent;
    (*tptr) = child;

    pdp->height = Max(GetHeight(avl, pdp->left), GetHeight(avl, pdp->right)) + 1;
    cdp->height = Max(GetHeight(avl, cdp->left), GetHeight(avl, cdp->right)) + 1;
}

/*  rotates to the right (p: parent , c: child)
         p                  c
        / \                / \
       c   Z    ======    X   p
      / \                    / \
     X   Y                  Y   Z
 */
static void RotateRight(avlADT avl, treeT *tptr)
{
    treeT parent, child;
    avlDataT *pdp, *cdp;

    parent = *tptr;
    pdp = AVLData(avl, parent);
    child = pdp->left;
    cdp = AVLData(avl, child);
    pdp->left = cdp->right;
    cdp->right = parent;
    (*tptr) = child;

    pdp->height = Max(GetHeight(avl, pdp->left), GetHeight(avl, pdp->right)) + 1;
    cdp->height = Max(GetHeight(avl, cdp->left), GetHeight(avl, cdp->right)) + 1;
}

void MapAVL(nodeFnT fn, avlADT avl, traversalOrderT order, void *clientData)
{
    RecMapAVL(fn, avl, avl->root, order, clientData);
}

static void RecMapAVL(nodeFnT fn, avlADT avl, treeT t, traversalOrderT order, void *clientData)
{
    avlDataT *dp;

    if (t != NULL) {
        dp = AVLData(avl, t);
        if (order == PreOrder) fn(t, clientData);
        RecMapAVL(fn, avl, dp->left, order, clientData);
        if (order == InOrder) fn(t, clientData);
        RecMapAVL(fn, avl, dp->right, order, clientData);
        if (order == PostOrder) fn(t, clientData);
    }
}

void *AVLRoot(avlADT avl)
{
    return (avl->root);
}

void *AVLLeftChild(avlADT avl, void *np)
{
    avlDataT *dp;

    if (np == NULL) Error("AVLLeftChild: Argument is NULL");
    dp = AVLData(avl, np);
    return (dp->left);
}

void *AVLRightChild(avlADT avl, void *np)
{
    avlDataT *dp;
    if (np == NULL) Error("AVLRightChild: Argument is NULL");
    dp = AVLData(avl, np);
    return (dp->right);
}

static avlDataT *AVLData(avlADT avl, treeT t)
{
    return  (avlDataT *) ((char *)t + avl->userSize );
}

static int GetHeight(avlADT avl, treeT t)
{
    avlDataT *dp;
    if (t == NULL)  return -1;

    dp = AVLData(avl, t);
    return dp->height;
}