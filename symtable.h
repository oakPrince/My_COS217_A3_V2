/* Interface for symtablehash.c and symtablelist.c that declares all the functions within the c programs. */
#include <stddef.h>
#ifndef SYMTABLE_INCLUDED
#define SYMTABLE_INCLUDED
/* A SymTable_T is a collection of items represented by key-value pairs in bindings. */
typedef struct SymTable *SymTable_T;
/* SymTable_T is a function that takes no arguments and 
returns a new SymTable with no bindings. 
If there is insufficient memory, it returns NULL. */
SymTable_T SymTable_new(void);
/* SymTable_free is a function that takes one argument, 
a SymTable_T type oSymTable, and frees all memory occupied by the SymTable_T object. */
void SymTable_free(SymTable_T oSymTable);
/* SymTable_getLength is a function that takes one argument, a SymTable_T type oSymTable, 
and returns the number of bindings in that SymTable_T as type size_t. */
size_t SymTable_getLength(SymTable_T oSymTable);
/* SymTable_put is a function that takes three arguments, a SymTable_T type oSymTable, 
a constant char pointer pcKey, and a constant pointer pvValue. If oSymTable does not have a binding with 
key pcKey, then SymTable_put adds a new binding to oSymTable with key pcKey and value pvValue and returns 1. Otherwise, 
the function leaves oSymTable unchanged and returns 0. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);
/* SymTable_replace is a function that takes three arguments, a SymTable_T type oSymTable, 
a constant char pointer pcKey, and a constant pointer pvValue. If oSymTable has a binding with
key pcKey, then the binding is replaced with pvValue and the old value is returned as an integer. Otherwise,
oSymTable is left the same and the function returns NULL. */ 
void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue);
/* SymTable_contains is a function that takes two arguments, a SymTable_T type oSymTable and 
a constant char pointer pcKey. If oSymTable contains a binding whose key is pcKey, the function returns 1. Else, it returns 0.*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);
/* SymTable_contains is a function that takes two arguments, a SymTable_T type oSymTable and 
a constant char pointer pcKey. This function returns the value of the binding within oSymTable whose key is pcKey. It returns NULL if no such binding exists. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);
/* SymTable_remove is a function that takes two arguments, a SymTable_T type oSymTable and 
a constant char pointer pcKey. It removes the binding with key pcKey from oSymTable and returns the binding's value. Otherwise, it returns NULL without changing oSymTable. */
void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);
/* SymTable_map is a function with three arguments, a SymTable_T type oSymTable, a function *pfApply with three constant char pointer arguments types (pcKey, pvValue, and pvExtra),
and a constant pointer pvExtra. The function applies the *pfApply function to each binding in oSymTable and passes pvExtra as an extra arguement. */
void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra);
#endif
