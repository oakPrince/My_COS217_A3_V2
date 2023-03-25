/* This code impleMents- a symbol table using a linked list  */

#include <assert.h>
#include <stdlib.h>
#include "stack.h"

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
  oSymTable = (SymTable_T)malloc(sizeof(struct List));
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
    psNextNode = psCurrentNode->psNextNode;
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
    if(psCurrentNode.key != NULL && psCurrentNode.value != NULL)
    {
      numOfBindings++;
    }
    psNextNode = psCurrentNode->psNextNode;
  }

  return numOfBindings;
  
}

/* The function SymTable_put takes three arguments: SymTable_T type oSymTable, constnat char pointer type pcKey, and constant pointer type pvValue. oSymTalbe is searched for if it contains key pcKey. If it does the binding is replaced with value pvValue. If not, oSymTable is not changed and the function returns NULL.  */

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct Node *psCurrentNode;
  struct Node *psNextNode;
  int oldVal;
  
  assert(oSymTable != NULL);

  for (psCurrentNode = oSymTable->first;
       psCurrentNode != NULL;
       psCurrentNode = psNextNode)
  {
    if(psCurrentNode.key == pcKey)
    {
      oldVal = psCurrentNode.value;
      psCurrentNode.value = pvValue;
      return oldVal;
    }
    psNextNode = psCurrentNode->psNextNode;
  }

  return NULL;
  
}

/* SymTable   */
