/*
 * File: symtab.h
 * --------------
 *This interface exports a simple symbol table abstraction.
 */

#ifndef _symtab_h
#define _symtab_h

#include "genlib.h"

/*
 * Type: symtabADT
 * ---------------
 * This type is the ADT used to represent a symbol table.
 */
typedef struct symtabCDT *symtabADT;

/*
 * Type: symtabFnT
 * ----------------
 * This type defines the class of functions that can be used to
 * map over the entries in a symbol table.
 */
typedef void (*symtabFnT) (string key, void *value, void *clientData);

/*
 * Function: NewSymbolTable
 * Usage: table = NewSymbolTable();
 * --------------------------------
 * This function allocates a new symbol table with no entries.
 */
symtabADT NewSymbolTable(void);

/*
 * Function: FreeSymbolTable
 * Usage: FreeSymbolTable(table);
 * -------------------------------
 * This function frees the storge associated with the symbol table.
 */
void FreeSymbolTable(symtabADT table);

/*
 * Function: Enter
 * Usage: Enter(table, key, value);
 * --------------------------------
 * This function associates key with value in the symbol table.
 * Each call to Enter supersedes any previous definition for key.
 */
void Enter(symtabADT table, string key, void *value);

/* 
 * Function: Lookup
 * Usage: value = Lookup(table, key);
 * ---------------------------------
 * This function returns the value associated with key in the symbol
 * table, or UNDEFINED, if no such value exists.
 */
void *Lookup(symtabADT table, string key);

/* 
 * Function: MapSymbolTable
 * Usgae: MapSymbolTable(fn, table, clientData);
 * ---------------------------------------------
 * This function goes through every in the symbol table
 * and calls the function fn, passing it the following arguments;
 * the current key, its associated value, and the clientData
 * pointer. The clientData pointer allows the client to pass
 * additional state information to the function fn, if necessary.
 * If no clientData argument is required, this value should be NULL.
 */
void MapSymbolTable(symtabFnT fn, symtabADT table, void *clientData);

#endif
