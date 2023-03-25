/* This code impleMents- a symbol table using a linked list  */

#include <assert.h>
#include <stdlib.h>
#include "symtable.h"

/* Each key-value binding pair is stored in a Node. Nodes are linked with pointers to form a linked list.  */

struct Node
{
  /* Key */
  const char *key;
  
  /* Value */
  int value;

  /* Pointer to next node */
  struct Node *next;
};

/* Begins linkedlist by pointing to first node */
struct SymTable
{
  struct Node *first;
};

/* Function returns empty symbol table is there is enought memeory. Otherwise,
   it returns null. */

SymTable_T SymTable_new(void)
{
  SymTable_T oSymTable;
  oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
  if (oSymTable == NULL)
    return NULL;
  oSymTable->first = NULL;
  return oSymTable;
}

/* Function takes one argument called oSymTable, a SymTable_T  type object, and frees all the memory occupied by the SymTable_T object. */

void SymTable_free(SymTable_T oSymTable)
{
  struct Node *psCurrentNode;
  struct Node *psNextNode;

  assert(oSymTable != NULL);

  for (psCurrentNode = oSymTable->first;
       psCurrentNode != NULL;
       psCurrentNode = psNextNode)
  {
    psNextNode = psCurrentNode->next;
    free(psCurrentNode);
  }

  free(oSymTable);
    
}

/* The function takes one arguement, oSymTable which is of type SymTable_T, and returns the number of bindings in oSymTable. */

size_t SymTable_getLength(SymTable_T oSymTable)
{
  size_t numOfBindings = 0;
  struct Node *psCurrentNode; 
  struct Node *psNextNode;
    
  assert(oSymTable != NULL);

  for(psCurrentNode = oSymTable->first;
      psCurrentNode != NULL;
      psCurrentNode = psNextNode)
  {
    if(psCurrentNode->key != NULL && psCurrentNode->value != NULL)
    {
      numOfBindings++;
    }
    psNextNode = psCurrentNode->next;
  }

  return numOfBindings;
  
}

/* The function SymTable_put takes three arguments: SymTable_T type oSymTable, constnat char pointer type pcKey, and constant pointer type pvValue. OSymTalbe is searched for if it contains key pcKey. If it does the function returns 1. If not the the key-value pair is added and the function returns zero.  */

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct Node *psCurrentNode;
  struct Node *psNextNode;
  struct Node *psNewNode;
  
  assert(oSymTable != NULL);

  for (psCurrentNode = oSymTable->first;
       psCurrentNode != NULL;
       psCurrentNode = psNextNode)
  {
    if(psCurrentNode->key == pcKey)
    {
      return 1;
    }
    psNextNode = psCurrentNode->next;
  }

  psNewNode = (struct Node*)malloc(sizeof(struct Node));
  if (psNewNode == NULL)
  {
    return 0;
  }
  psNewNode->key = pcKey;
  psNewNode->next = oSymTable->first;
  oSymTable->first = psNewNode;
  return 1;
  
}

/* SymTable_replace is a function that takes two arguements, a SymTable_T type oSymtable, a constant char pointer type pcKey, and a constant pointer type pvValue. If a bindinng with key pcKey is found in oSymtable, the value of the binding key-value pair is repalced and the old value is returned. Otherwise, oSymtalbe is left the same and the function returns NULL. */


void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct Node *psCurrentNode;
  struct Node *psNextNode;
  struct Node *psNewNode;
  int oldVal;

  assert(oSymTable != NULL);

  for (psCurrentNode = oSymTable->first;
       psCurrentNode != NULL;
       psCurrentNode = psNextNode)
  {
    if(psCurrentNode->key == pcKey)
    {
      oldVal = psCurrentNode->value;
      psCurrentNode->value = pvValue;
      return oldVal;
    }
  }

  return NULL;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
  struct Node *psCurrentNode;

  assert(oSymTable != NULL);

  for (psCurrentNode = oSymTable->first;
       psCurrentNode != NULL;
       psCurrentNode = psNextNode)
  {
    if(psCurrentNode->key == pcKey)
    {
      return  psCurrentNode->value;
    }
  }

  return NULL;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
  struct Node *psCurrentNode;
  struct Node *psNextNode;

  assert(oSymTable != NULL);

  for (psCurrentNode = oSymTable->first;
       psCurrentNode != NULL;
       psCurrentNode = psNextNode)
  {
     if(psCurrentNode->key == pcKey)
    {
      
      
      
    }
  }

  return NULL;
}

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{
  struct Node *psCurrentNode;

  assert(oSymTable != NULL);
  assert(pfApply != NULL);

  for (psCurrentNode = oSymTable->first;
       psCurrentNode != NULL;
       psCurrentNode = psCurrentNode->next)
  {
    (*pfApply)((void*)psCurrentNode->key, (void*)psCurrentNode->value, (void*)pvExtra);
  }
}
