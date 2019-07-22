/*
 *File: scanadt.h
 *---------------
 * On the Page of 275
 *
 * This file is the interfacd to a module that exports an abstract data type
 * to facilitate dividing a string into logical units called "bokens" which 
 * are either
 *
 */

#ifndef _scanadt_h
#define _scanadt_h

#include "genlib.h"

/*
 * Type: scannerADT
 * ----------------
 * This type is the abstract type used to represent a single instance
 * of a scanner. As with any abstract type, the details of the internal
 * representation are hidden from the client.
 */
typedef struct scannerCDT *scannerADT;

/*
 * Function: NewScanner
 * Usage: scanner = NewScanner();
 * ------------------------------
 * This function create a new scanner instance. All other functions
 * in this interface take this scanner value as their first argument
 * so that they can identify what particular instance of the scanner
 * is in use. This design makes it possible for clients to have more
 * than one scanner process active at the same time.
 */
scannerADT NewScanner(void);

/*
 * Function: FreeScanner
 * Usage: FreeScanner(scanner);
 * ---------------------------
 * This function frees the storage associated with scanner
 */
void FreeScanner(scannerADT scanner);

/*
 * Function: SetScannerString
 * Usage: SetScannerString(scanner, str);
 * ---------------------------------------
 * This function initializes the scanner so that it will start
 * extracting tokens from the string str.
 */
void SetScannerString(scannerADT scanner, string str);

/*
 * Function: ReadToken
 * Usage: token = ReadToken(scanner);
 * ----------------------------------
 * This function returns the next token from scanner. If 
 * ReadToken is called when no tokens are available, it returns
 * the empty string. The token returned by ReadToken is always
 * allocated in the heap, which means that clients can call FreeBlock
 * when the token is no longer needed.
 */
string ReadToken(scannerADT scanner);

/*
 * Function: MoreTokenExist
 * Usage: if( MoreTokenExist(scanner) ) ...
 * ------------------------------------------
 * This function returns TRUE as long as there are additional
 * tokens for the scanner to read.
 */
bool MoreTokensExist (scannerADT scanner);

/*
 * Function: SaveToken
 * Usage: SvaeToken(scanner, token);
 * ---------------------------------
 * This function stores the token in the scanner data structure
 * in such a way that the next time ReadToken is called, it will
 * return that token without reading any additional characters
 * from the input.
 */
void Savetoken(scannerADT scanner, string token);

/*
 * Function: SetScannerSpaceOption, GetScannerSpaceOption
 * Usage: SetScannerSpaceOption(scanner, option);
 *        option = GetScannerSpaceOption(scanner);
 * -----------------------------------------------
 * The SetScannerSpaceOption function controls whether the scanner
 * ignores whitespace characters or treats them as valid tokens.
 * By default, the ReadToken function treats whitespace characters,
 * such as spaces and tabs, just like any other punctuation mark.
 * If, however, you call
 *
 *     SetScannerSpaceOption(scanner, IgnoreSpace);
 *
 * The GetScannerSpaceOption function returns the current setting
 * of this option.
 */
typedef enum {PreserveSpaces, IgnoreSpaces} spaceOptionT;

void SetScannerSpaceOption(scannerADT scanner, spaceOptionT option);
spaceOptionT GetScannerSpaceOption(scannerADT scanner);

#endif

/*
 * The following code fragment serves as an idiom for processing
 * each token in the string input Sting:
 * 
 *     scanner = NewScanner();
 *     SetScannerString(scanner, inputString);
 *     while(MoreTokensExist(scanner)){
 *         token = ReadToken(scanner);
 *         . . . process the token ...
 *      }
 * This version of scanadt.h also supports the folowing extensions, 
 * which are documented later in the interface:
 * 
 *     SaveToken
 *     SetScannerSpaceOption
 */
