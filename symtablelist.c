/* This code impleMents- a symbol table using a linked list  */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "symtable.h"

/* Each key-value binding pair is stored in a Node. Nodes are linked with pointers to form a linked list.  */

struct SymTableNode
{
  /* Key */
  const char *key;
  
  /* Value */
  void *value;

  /* Pointer to next node */
  struct SymTableNode *next;
};

/* Begins linkedlist by pointing to first node */
struct SymTable
{
  struct SymTableNode *first;

  size_t length;
};

/* Function returns empty symbol table is there is enought memeory. Otherwise,
   it returns null. */

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

/* Function takes one argument called oSymTable, a SymTable_T  type object, and frees all the memory occupied by the SymTable_T object. */

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

/* The function takes one arguement, oSymTable which is of type SymTable_T, and returns the number of bindings in oSymTable. */

size_t SymTable_getLength(SymTable_T oSymTable)
{
  size_t numOfBindings = 0;
  struct SymTableNode *current; 
  struct SymTableNode *forward;
    
  assert(oSymTable != NULL);

  for(current = oSymTable->first;
      current != NULL;
      current = forward)
  {
    if(current->key != NULL)
    {
      numOfBindings++;
    }
    forward = current->next;
    free(current);
  }

  return numOfBindings;
  
}

/* The function SymTable_put takes three arguments: SymTable_T type oSymTable, constnat char pointer type pcKey, and constant pointer type pvValue. OSymTalbe is searched for if it contains key pcKey. If it does the function returns 1. If not the the key-value pair is added and the function returns zero.  */

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct SymTableNode *current;
  struct SymTableNode *forward;
  struct SymTableNode *newNode;
  char *defCopyofKey;
    
  assert(oSymTable != NULL);
  assert(pcKey != NULL);
  assert(pvValue != NULL);

  newNode = malloc(sizeof(struct SymTableNode));
  if (newNode == NULL)
  {
    return 0;
  }

  defCopyofKey = (char*)malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    free(newNode);
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  newNode->key = NULL;
  
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
    forward  = current->next;
  }
  			      
  newNode->key = defCopyofKey;
  newNode->value = (void*) pvValue;
  newNode->next = oSymTable->first;
  oSymTable->first = newNode;  
  return 1;
  
}

/* SymTable_replace is a function that takes two arguements, a SymTable_T type oSymtable, a constant char pointer type pcKey, and a constant pointer type pvValue. If a bindinng with key pcKey is found in oSymtable, the value of the binding key-value pair is repalced and the old value is returned. Otherwise, oSymtalbe is left the same and the function returns NULL. */

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct SymTableNode *current;
  struct SymTableNode *forward;
  char *defCopyofKey;

  assert(oSymTable != NULL);
  assert(pcKey != NULL);
  assert(pvValue != NULL);
  
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  for (current = oSymTable->first;
       current != NULL;
       current = forward)
  {
    if (strcmp(current->key, defCopyofKey) == 0)
    {
      void *oldVal = current->value;
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

  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);
  
  for (current = oSymTable->first;
       current != NULL;
       current = forward)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      return 1;
    }
    forward  = current->next;
  }

  return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
  struct SymTableNode *current;
  struct SymTableNode *forward;
  char *defCopyofKey;
  
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);
  
  for (current = oSymTable->first;
       current != NULL;
       current = forward)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      void *foundVal = current->value;
      return foundVal;
    }
    forward = current->next;
  }
  return NULL;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
 const void *holdVal;
 struct SymTableNode *forward;

 assert(oSymTable != NULL);
 assert(pcKey != NULL);

 if(SymTable_contains(oSymTable, pcKey) == 1)
 {
   holdVal = oSymTable->first->value;
   forward = oSymTable->first->next;
   free(oSymTable->first);
   oSymTable->first = forward;
   return (void*) holdVal;
 }

 return NULL;
}

void SymTable_map(SymTable_T  oSymTable, void(*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{
 struct SymTableNode *current;
 struct SymTableNode *forward;

 assert(oSymTable != NULL);
 assert(pfApply != NULL);
 assert(pvExtra != NULL);

 for (current = oSymTable->first;
      current != NULL;
      current = forward)
 {
   (*pfApply)((void*)current->key, (void*)current->value, (void*)pvExtra);
   forward = current->next;
 }
}
