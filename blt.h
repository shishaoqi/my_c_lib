/* 
 * File: bst.h
 * ------------
 * This file provides an interface for a general binary search
 * tree facility that allows the to maintain control of the 
 * structure of the node.
 */

#ifndef _blt_h
#define _blt_h

#include "genlib.h"
#include "cmpfn.h"

/* 
 * Type: bstADT
 *--------------
 * This is the abstract type for a binary search tree.
 */
typedef struct bstCDT *bstADT;

/*
 * Type: nodeFnT
 * ----------------
 * This tpe defines the class of callback functions for nodes.
 */
typedef void (*nodeFnT) (void *np, void *clientData);

/* 
 * Type: nodeIniFnT
 * -----------------
 * This type defines the class of functions used to initialize
 * a newly created node.
 */
typedef void (*nodeInitFnT) (void *np, void *kp, void *clientData);

/*
 *Type: deleteT
 * -----------------
 * This type use in function DeleteBSTNode(bstADT bst, void *kp) return element
 * type. isNull is indicate that function DeleteBSTNode(bstADT bst, void *kp)
 * success delete the kp node.
 */
typedef struct deleteE *deleteT;


bstADT NewBST(int size, cmpFnT cmpFn, nodeInitFnT nodeInitFn);

void FreeBST(bstADT bst, nodeFnT freeNodeFn);

void *FindBSTNode(bstADT bst, void *kp);

int InsertBSTNode(bstADT bst, void *kp, void *clientData);

void *DeleteBSTNode(bstADT bst, void *kp);

typedef enum { InOrder, PreOrder, PostOrder } OrderT;
void MapBST(nodeFnT fn, bstADT bst, OrderT order, void *clientData);

/* 
 * Low-level functions: BSTRoot, BSTLeftChild, BSTRightChild
 * Usage: root = BSTRoot(bst);
 *        child = BSTLeftChild(bst, np);
 *        child = BSTRightChild(bst, np);
 * --------------------------------------
 */
void *BSTRoot(bstADT bst);
void *BSTLeftChild(bstADT bst, void *np);
void *BSTRightChild(bstADT bst, void *np);

#endif

