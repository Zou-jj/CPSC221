#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  Node *newNode = new Node(ndata);
  newNode -> prev = p;
  if (p != NULL){
    p -> next = newNode;
  } else {
    head_ = newNode;
  }
  length_++;
  return newNode;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  if (p != NULL && q != NULL && p != q){
    Node *tempPPrev = p -> prev;
    Node *tempPNext = p -> next;
    Node *tempQPrev = q -> prev;
    Node *tempQNext = q -> next;

    if (p -> next == q){
      p -> prev = q;
      p -> next = q -> next;
      q -> prev = tempPPrev;
      q -> next = p;
      if (tempPPrev == NULL){
        head_ = q;
      } else {
        tempPPrev -> next = q;
      }
      if (tempQNext == NULL){
      } else {
        tempQNext -> prev = p;
      }
    } else if (q -> next == p){
      p -> prev = q -> prev;
      p -> next = q;
      q -> prev = p;
      q -> next = tempPNext;
      if (tempPNext == NULL){
      } else {
        tempPNext -> prev = q;
      }
      if (tempQPrev == NULL){
        head_ = p;
      } else {
        tempQPrev -> next = p;
      }
    } else {
      p -> prev = q -> prev;
      p -> next = q -> next;
      q -> prev = tempPPrev;
      q -> next = tempPNext;
      if (tempPPrev == NULL){
        tempPNext -> prev = q;
        head_ = q;
      } else if (tempPNext == NULL){
        tempPPrev -> next = q;
      } else {
        tempPNext -> prev = q;
        tempPPrev -> next = q;
      }
      if (tempQPrev == NULL){
        tempQNext -> prev = p;
        head_ = p;
      } else if (tempQNext == NULL){
        tempQPrev -> next = p;
      } else {
        tempQNext -> prev = p;
        tempQPrev -> next = p;
      }
    }
  }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  if (head_ == NULL){
    return;
  }
  Node* temp = head_;
  while (temp -> next != NULL){
    temp = temp -> next;
    delete temp -> prev;
  }
  delete temp;
  temp = NULL;
  head_ = NULL;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  if (other.head_ != NULL){
    head_ = new Node(other.head_->data);
    length_ = other.length_;
    Node* curr = head_;
    Node* currOther = other.head_;
    while(currOther->next != NULL) {
      curr->next = new Node(currOther->next->data);
      curr->next->prev = curr;
      curr = curr->next;
      currOther = currOther->next;
    }
  }
}

/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block 
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  Node *curr = head_;
  Node *comp = NULL;
  int count;
  double minDisHead = 1.0;
  if (curr == NULL){
    return;
  } else {
    count = 1;
  }
  if (curr -> next != NULL){
    comp = curr -> next;
    count++;
  } else {
    return;
  }
  while (comp -> next != NULL){
    if (comp -> data.distanceTo(curr -> data) < minDisHead){
      minDisHead = comp -> data.distanceTo(curr -> data);
    }
    count++;
    comp = comp -> next;
  }
  double *minDis = (double *) malloc(count * sizeof(double));
  minDis[0] = minDisHead;
  double maxDis = minDisHead;
  int maxIndex = 0;
  Node *newHead = head_;

  Node *tempHead = head_ -> next;
  for (int i = 1; i < count ; i++){
    Node *tempCurr = tempHead;
    Node *tempComp = head_;
    double minDisTemp = 1.0;
    for (int j = 0; j < count; j++){
      if (i == j){
        continue;
      }
      if (tempCurr -> data.distanceTo(tempComp -> data) < minDisTemp){
        minDisTemp = tempComp -> data.distanceTo(tempCurr -> data);
      }
      tempComp = tempComp -> next;
    }
    minDis[i] = minDisTemp;
    if (minDisTemp > maxDis){
      maxDis = minDisTemp;
      maxIndex = i;
      newHead = tempHead;
    }
    tempHead = tempHead -> next;
  }
  swap(head_, newHead);
  free(minDis);

  curr = head_;
  while (curr != NULL) {
    comp = curr -> next;
    Node *nextNode;
    double minDisNext = 1;
    while (comp != NULL){
      if((curr->data).distanceTo(comp->data) < minDisNext) {
        nextNode = comp;
        minDisNext = (curr -> data).distanceTo(comp -> data);
      }
      comp = comp -> next;
    }
    swap(curr->next, nextNode);
    curr = curr->next;
  }
}
