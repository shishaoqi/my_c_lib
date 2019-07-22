/*
 * File: rbt.h
 * -----------
 * This file provides an interface for a general binary search
 * tree facility that allows the client to maintain control of
 * the structure of the node.
 */

#ifndef _rbt_h
#define _rbt_h

#include "genlib.h"
#include "cmpfn.h"

/*
 * Type: rbtADT
 * ------------
 * This is the abstract type for a binary search tree.
 */

typedef struct rbtCDT *rbtADT;

/*
 * Type: nodeFnT
 * -------------
 * This type defines the class of callback functions for nodes.
 */

typedef void (*nodeFnT)(void *np, void *clientData);

/*
 * Type: nodeInitFnT
 * -----------------
 * This type defines the class of functions used to initialize
 * a newly created node.
 */

typedef void (*nodeInitFnT)(void *np, void *kp, void *clientData);

/*
 * Function: NewRBT
 * Usage: rbt = NewRBT(sizeof (nodeT), cmpFn, nodeInitFn);
 * -------------------------------------------------------
 * This function allocates and returns a new empty binary search
 * tree.  The first argument is the size of the client node.  The
 * second is a comparison function, which is called with the address
 * of the search key and the address of a node.  By storing the key
 * at the beginning of the structure, client's can use the standard
 * comparison functions from cmpfn.h.  The third argument is a
 * function that initializes the client's fields in the node, which
 * is described in more detail in the comments for InsertRBTNode.
 */

rbtADT NewRBT(int size, cmpFnT cmpFn, nodeInitFnT nodeInitFn);

/*
 * Function: FreeRBT
 * Usage: FreeRBT(rbt, freeNodeFn);
 * --------------------------------
 * This function frees the storage for a tree, but calls the
 * client-supplied freeNodeFn to free each individual node.
 * The clientData value passed to the callback function is
 * always NULL.
 */

void FreeRBT(rbtADT rbt, nodeFnT freeNodeFn);

/*
 * Function: FindRBTNode
 * Usage: np = FindRBTNode(rbt, &key);
 * -----------------------------------
 * This function applies the binary search algorithm to find a
 * particular key in the tree represented by rbt.  The second
 * argument represents the address of the key in the client
 * space rather than the key itself, which makes it possible to
 * use this package for keys that are not pointer types.  If a
 * node matching the key appears in the tree, FindRBTNode
 * returns a pointer to it; if not, FindRBTNode returns NULL.
 */

void *FindRBTNode(rbtADT rbt, void *kp);

/*
 * Function: InsertRBTNode
 * Usage: np = InsertRBTNode(rbt, &key, clientData);
 * -------------------------------------------------
 * This function is used to insert a new node into a binary search
 * tree.  The rbt and &key arguments are interpreted as they are
 * in FindRBTNode.  If the key already exists, the result is
 * simply the address of the old node.  If the key is not found,
 * InsertRBTNode allocates a new node and then calls the node
 * initialization function specified in the NewRBT call to
 * initialize it.  The call has the following form:
 *
 *     nodeInitFn(np, kp, clientData);
 *
 * where np is a pointer to the node, kp is the pointer to the key,
 * and clientData is the value (typically NULL) supplied in the
 * InsertRBTNode call.  The initialization function must initialize
 * the key field in the node, but may perform other initialization
 * as well.
 */

void *InsertRBTNode(rbtADT rbt, void *kp, void *clientData);

/*
 * Function: DeleteRBTNode
 * Usage: np = DeleteRBTNode(rbt, &key);
 * -------------------------------------
 * This function deletes a node in the tree that matches the
 * specified key pointer.  The arguments are interpreted as
 * in FindRBTNode.  The function returns the address of the
 * deleted node so that clients can free its storage.  If the
 * key is not found in the tree, DeleteRBTNode returns NULL.
 */

void *DeleteRBTNode(rbtADT rbt, void *kp);

/*
 * Function: MapRBT
 * Usage: MapRBT(fn, rbt, order, clientData);
 * ------------------------------------------
 * This function calls fn on every node in the binary search tree,
 * passing it a pointer to a node and the clientData pointer.  The
 * type of traversal is given by the order argument, which must
 * be one of the constants InOrder, PreOrder, or PostOrder.
 */

typedef enum { InOrder, PreOrder, PostOrder } traversalOrderT;

void MapRBT(nodeFnT fn, rbtADT rbt, traversalOrderT order,
            void *clientData);

/*
 * Low-level functions: RBTRoot, RBTLeftChild, RBTRightChild
 * Usage: root = RBTRoot(rbt);
 *        child = RBTLeftChild(rbt, np);
 *        child = RBTRightChild(rbt, np);
 * ---------------------------------------------------------
 * These functions allow the client to trace the structure of the
 * binary search tree and are useful primarily for debugging.
 */

void *RBTRoot(rbtADT rbt);
void *RBTLeftChild(rbtADT rbt, void *np);
void *RBTRightChild(rbtADT rbt, void *np);

#endif
