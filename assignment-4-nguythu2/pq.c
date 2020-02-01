/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Thuy-Vy Nguyen
 * Email: nguythu2@oregonstate.edu
 */

#include "pq.h"
#include <stdlib.h>
#include <assert.h>
#include "dynarray.h"
#include <stdio.h>
#include <string.h>


/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq_element{
  void * value;
  int priority;
};

struct pq{
  struct dynarray * array; //an array of struct pq_element
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */


struct pq_element * pq_element_create( void * value, int priority){
    struct pq_element * element = malloc(sizeof(struct pq_element));
    element->priority = priority;
    element->value = value;
    return element;
}

void free_element(struct pq_element * element){
  assert(element);
  free(element);
}

struct pq* pq_create() {
  struct pq * pq = malloc(sizeof(struct pq));
  pq->array = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  int i;
  assert(pq);
/*
  for (i = 0; i < dynarray_size(pq->array); i++){
    free_element(pq->array,)
  }
*/
  dynarray_free(pq->array);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */


int pq_isempty(struct pq* pq) {
  assert(pq->array);
  return dynarray_size(pq->array) == 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */


//function: swap
//description: swaps the indexes of the array & i and j
//parameters: the array and indexes of the array to be swapped
void swap(struct pq * pq, int i, int j){
  struct pq_element * temp = dynarray_get(pq->array,i);
  struct pq_element * temp1 = dynarray_get(pq->array,j);

  dynarray_set(pq->array,i,temp1);
  dynarray_set(pq->array,j,temp);

}


void percolate_up(struct pq * pq, int i){
  struct pq_element *current = dynarray_get(pq->array,i);
  struct pq_element *parent = dynarray_get(pq->array,(i-1)/2);

  while( (current->priority < parent->priority) && i > 0) {
    swap(pq,i,(i-1)/2);
    i = (i-1)/2;
    current = dynarray_get(pq->array,i);
    parent = dynarray_get(pq->array, (i-1)/2);
   }


}

void pq_insert(struct pq* pq, void * value, int priority) {
  struct pq_element * item = pq_element_create(value,priority);

  dynarray_insert(pq->array,-1,item);
  percolate_up(pq,dynarray_size(pq->array)-1);

}





void pq_print_debug(struct pq* pq, int total) {
  struct pq_element * element = dynarray_get(pq->array,0);

  for (int i = 0; i < total; i++) {
    element = dynarray_get(pq->array,i);
    printf("i=%d pq_print_debug = %d\n", i, element->priority);
  }
}



/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  struct pq_element * element = dynarray_get(pq->array,0);
  return element->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  assert(pq->array);
  struct pq_element * element = dynarray_get(pq->array,0);
  return element->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

 int min_priority( struct dynarray * array, int i, struct pq_element * left, struct pq_element * right){
   if (left->priority > right->priority){
     return right->priority;
   }
   else{
     return left->priority;

 }
}

 int min( struct dynarray * array, int i, struct pq_element * left, struct pq_element * right){
   if (left->priority > right->priority){
     return i*2+2;
   }
   else{
     return i*2+1;
   }
 }


 void percolate_down(struct pq * pq, int i){
   struct pq_element * current = dynarray_get(pq->array,i);
   struct pq_element * left = dynarray_get(pq->array,2*i +1);
   struct pq_element * right = dynarray_get(pq->array,2*i +2);

   int bool = 0;


   while(bool == 0 && current->priority > min_priority(pq->array,i,left,right)){ //compares priority between current and smaller child
     swap(pq,i,min(pq->array,i,left,right));
     current = dynarray_get(pq->array, min(pq->array,i,left,right));
     i = min(pq->array,i,left,right);
     if ( 2*i + 2 <= dynarray_size(pq->array)-1){ //both children good
       left = dynarray_get(pq->array,2*i +1);
       right = dynarray_get(pq->array,2*i +2);
     }
     else if(2*i +1 <= dynarray_size(pq->array)-1){ //only left child good
       bool = 1;
       left = dynarray_get(pq->array,2*i +1);
       if( current->priority > left->priority){
         swap(pq,i,min(pq->array,i,left,right));
       }
     }
     else { //no children good
      bool = 1;
     }
 }
}

void* pq_remove_first(struct pq* pq) {
  void * og = ((struct pq_element *) dynarray_get(pq->array, 0))->value;
  free(dynarray_get(pq->array,0));
  dynarray_set(pq->array,0,dynarray_get(pq->array,dynarray_size(pq->array)-1));
  dynarray_remove(pq->array,dynarray_size(pq->array)-1);

  if (dynarray_size(pq->array) > 2){
    percolate_down(pq,0);
  }

  return og;
}
