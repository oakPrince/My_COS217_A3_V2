/* This code implements a symbol table using a linked list  */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "symtable.h"

/* Each key-value binding pair is stored in a SymTableNode structure.
 Nodes are linked with pointers to form a linked list. */

struct SymTableNode
{
  /* Constant char pointer contains key */
  const char *key;
  /* Constant void pointer contains value */
  void *value;
  /* Structure points to next SymTableNode structure in linked list */
  struct SymTableNode *next;
};

/* SymTable structure begins linked list */
struct SymTable
{
  /* Points to first SymTableNode in linked list */
  struct SymTableNode *first;
  /* Length of linked list */
  size_t length;
};

SymTable_T SymTable_new(void)
{
  SymTable_T oSymTable;
  oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
  if (oSymTable == NULL)
  {
    return NULL;
  }
  oSymTable->length = 0;
  oSymTable->first = NULL;
  return oSymTable;
}

void SymTable_free(SymTable_T oSymTable)
{
  struct SymTableNode *current;
  struct SymTableNode *forward;
  
  assert(oSymTable != NULL);

  for (current = oSymTable->first;
       current != NULL;
       current = forward)
  {
    forward = current->next;
    free((void*) current->key);
    free(current);
  }

  free(oSymTable);
    
}

size_t SymTable_getLength(SymTable_T oSymTable)
{

  assert(oSymTable != NULL);

  return oSymTable->length;
  
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct SymTableNode *current;
  struct SymTableNode *forward;
  struct SymTableNode *newNode;
  char *defCopyofKey;
    
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /* allocate memory for newNode structure */
  newNode = malloc(sizeof(struct SymTableNode));
  if (newNode == NULL)
  {
    return 0;
  }

  /* create defensive copy */
  defCopyofKey = (char*)malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    free(newNode);
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  /* search SymTable_T structure to see if there are any
 bindings with keys that are the same as pcKey */
  
  for (current = oSymTable->first;
       current != NULL;
       current = forward)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      free(newNode);
      return 0;
    }
    forward = current->next;
  }

  /* add new node to the front of the linked list */     
  newNode->key = defCopyofKey;
  newNode->value = (void*) pvValue;
  newNode->next = oSymTable->first;
  oSymTable->first = newNode;
  oSymTable->length++;
  return 1;
  
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct SymTableNode *current;
  struct SymTableNode *forward;
  void *oldVal;
  char *defCopyofKey;

  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  /* Search SymTable_T structure to see if
 it has a binding with a key matching pcKey.
 If it does, change the value of that SymTableNode to pvValue.
 Then, return the old value. */  
  for (current = oSymTable->first;
       current != NULL;
       current = forward)
  {
    if (strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      oldVal = current->value;
      current->value = (void*) pvValue;
      return oldVal;
    }
    forward = current->next;
  }

  return NULL;

}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
  struct SymTableNode *current;
  struct SymTableNode *forward;
  char *defCopyofKey;
  
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  /* search SymTable_T structure for any key-value pairs that have the key pcKey.
 If there is a match, return 1. If not, return 0 */
  for (current = oSymTable->first;
       current != NULL;
       current = forward)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      return 1;
    }
    forward = current->next;
  }

  free(defCopyofKey);
  return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
  struct SymTableNode *current;
  struct SymTableNode *forward;
  char *defCopyofKey;
  void *foundVal;
    
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  /* Search SymTable_T structure for any bindings with pcKey as the key.
     If there is a binding with pcKey, the value of that binding is returned. If not, NULL is returned. */  
  for (current = oSymTable->first;
       current != NULL;
       current = forward)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      foundVal = current->value;
      return foundVal;
    }
    forward = current->next;
  }
  return NULL;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
 const void *holdVal;
 struct SymTableNode *previous;
 struct SymTableNode *current;
 struct SymTableNode *forward;
 char *defCopyofKey;

 assert(oSymTable != NULL);
 assert(pcKey != NULL);

 /* Base Case: if SymTable_T structure is empty. */
 if (oSymTable->length == 0)
 {
   return NULL;
 }
 
 /* create defensive copy */
 defCopyofKey = (char*)malloc(strlen(pcKey) + 1);
 if (defCopyofKey == NULL)
 {
   return 0;
 }
 strcpy(defCopyofKey, pcKey);

 /* Base Case: if SymTable_T structure has only one SymTableNode */
 if(strcmp(oSymTable->first->key, defCopyofKey) == 0)
 {
     free(defCopyofKey);
     holdVal = oSymTable->first->value;
     forward = oSymTable->first->next;
     free((void*) oSymTable->first->key);
     free(oSymTable->first);
     oSymTable->first = forward;
     oSymTable->length--;
     return (void*) holdVal;
 }
 else
 {   
   free(defCopyofKey);
   return NULL;
 }
 
 previous = oSymTable->first;
 
 /* If a binding in the SymTable_T structure has a key that matches pcKey,
 the SymTableNode is removed from the SymTable strucutre and the binding's value is returned.
 Otherwise, NULL is returned. */   
 for (current = oSymTable->first;
      current != NULL;
      current = forward)
   {
     if(strcmp(current->key, defCopyofKey) == 0)
     {
       free(defCopyofKey);
       holdVal = current->value;
       forward = current->next;
       previous->next = forward;
       free((void*) current->key);
       free(current);
       oSymTable->length--;
       return (void*) holdVal;
     }
     forward = current->next;
     previous = current;
   }

 free(defCopyofKey);
 return NULL;
}

void SymTable_map(SymTable_T  oSymTable, void(*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{
 struct SymTableNode *current;
 struct SymTableNode *forward;

 assert(oSymTable != NULL);
 assert(pfApply != NULL);

 /* applies pfApply function to every binding in SymTable_T structure */
 for (current = oSymTable->first;
      current != NULL;
      current = forward)
 {
   (*pfApply)((void*)current->key, (void*)current->value, (void*)pvExtra);
   forward = current->next;
 }
}
