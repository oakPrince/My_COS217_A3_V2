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
struct List
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
