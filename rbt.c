/*
* @Author: shishao
* @Date:   2019-07-15 10:06:28
* @Last Modified by:   shishao
* @Last Modified time: 2019-07-15 23:02:06
*/

#include <stdio.h>
#include "genlib.h"
#include "cmpfn.h"
#include "rbt.h"

typedef void *treeT;

struct rbtCDT {
    treeT root;
    int userSize, totalSize;
    cmpFnT cmpFn;
    nodeInitFnT nodeInitFn;
}

typedef enum { black, red } colorT;

typedef struct {
    colorT color;
    treeT left, right;
} rbtDataT;

/* Private function prototypes */

static treeT *RecFindNode(rbtADT rbt, treeT t, void *kp);
static void *RecInsertNode(rbtADT rbt, treeT *tptr, void *kp,
                           void *clientData);
static void *RecDeleteNode(rbtADT rbt, treeT *tptr, void *kp);
static void *DeleteTargetNode(rbtADT rbt, treeT *tptr);
static void RecMapRBT(nodeFnT fn, rbtADT rbt, treeT t,
                      traversalOrderT order, void *clientData);
static rbtDataT *RBTData(rbtADT rbt, treeT t);


rbtADT NewRBT(int size, cmpFnT cmpFn, nodeInitFnT nodeInitFn)
{
    rbtADT rbt;

    rbt = New(rbtADT);
    rbt->root = NULL;
    rbt->userSize = size;
    rbt->totalSize = rbt->userSize + sizeof(rbtDataT);
    rbt->cmpFn = cmpFn;
    rbt->nodeInitFn = nodeInitFn;

    return rbt;
}

void *InsertRBTNode(rbtADT rbt, void *kp, void *clientData)
{
    return (RecInsertNode(rbt, &rbt->root, kp, clientData));
}

static void *RecInsertNode(rbtADT rbt, treeT *tptr, void *kp,
                            void *clientData)
{
    brtDataT *dp;
    treeT t;
    int sign;

    t = *tptr;
    if (t == NULL) {
        t = GetBlock(rbt->totalSize);
        rbt->nodeInitFn(t, kp, clientData);
        dp = BSTData(rbt, t);
        dp->left = dp->right = NULL;
        *tptr = t;
        return (t);
    }

    sign = brt->cmpFn(kp, t);
    if (sign == 0)  return (t);
    dp = RBTData(rbt, t);
    if (sign < 0) {
        return (RecInsertNode(rbt, &dp->left, kp, clientData));
    } else {
        return (RecInsertNode(rbt, &dp->right, kp, clientData));
    }
}