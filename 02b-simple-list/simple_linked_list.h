/**********************************************************************************************
 * NIU CSCI 340 Section 0003                                                                  *
 * Assignment 2b                                                                              *
 * simple_linked_list.h                                                                       *
 * Phoenix Chheav - Z1966108 - phoenixchh                                                     *
 *                                                                                            *
 *   I certify that everything I am submitting is either provided by the professor for use in *
 * the assignment, or work done by me personally. I understand that if I am caught submitting *
 * the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic    *
 * Misconduct and will be punished as such.                                                   *
 *                                                                                            *
 **********************************************************************************************/
#ifndef NIUCSCI340_LIST_H
#define NIUCSCI340_LIST_H

#include "simple_linked_list.decl.h"

#include <iostream>
#include <vector>
#include <list>

#warning The provided version of simple_linked_list.h does not actually implement things. You will likely get compilation errors until you've at least partially implemented them. You can remove this warning once you've read it.

using std::list;
using std::vector;
using std::underflow_error;

/**
 * @brief simply_linked_list(range constuctor): initializes the list to a working state, iterates over the ranges
 *                           provides and add each element to the linked list in order. Only call with valid iterator ranges.
 * 
 * @tparam T 
 * @tparam ITERATOR 
 * @param beg the beginning of the range
 * @param end the end of the range
 */
template <typename T>
template <typename ITERATOR> // constructor copying the contents of another container
simple_linked_list <T>::simple_linked_list(ITERATOR beg, ITERATOR end) {
  for(ITERATOR i = beg; i != end; ++i){
    push_back(*i);
  }
}

/**
 * @brief empty(): to check if there are anymore nodes in the linked_list
 * 
 * @tparam T 
 * @return true if there are no more nodes
 * @return false if there are no more nodes in the linked-list
 */
template <typename T>
bool simple_linked_list<T>::empty() const {
  if(n_elements == 0){
    return true;
  }
  return false;
}

/**
 * @brief begin(): function that point the the head node
 * 
 * @tparam T 
 * @return return the simple_linked_list that point to the head node
 */
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::begin() {
  simple_linked_iterator<T> simple_linked(head);
  return simple_linked;
}

/**
 * @brief end(): function that point to the end node
 * 
 * @tparam T 
 * @return return simple_linked_list that compare the iterator that is off the end of the list
 */
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::end() {
  simple_linked_iterator<T> simple_linked(tail);
  return simple_linked;
}

/**
 * @brief front() check if the list is empty or not, if not return a reference
 * 
 * @tparam T 
 * @return return a reference to data member of the head node
 */
template <typename T>
T & simple_linked_list<T>::front() {
  if(empty()){
    throw underflow_error("underflow exception on call front()");
  }
  return head->data; 
}
    
/**
 * @brief back() check if the list is empty or not, if not return a reference
 * 
 * @tparam T 
 * @return return a reference to data member of the tail node
 */
template <typename T>
T & simple_linked_list<T>::back() {
  if(empty()){
    throw underflow_error("underflow exception on call back()");
  }
  return tail->data;
}

/**
 * @brief popback(): remove element at the back of the list
 * 
 * @tparam T 
 */
template <typename T>
void simple_linked_list<T>::pop_back() {
  linked_node<T> *del_linked = head;//save address of node to delete in a pointer
  head = del_linked->next; //point head at the new last node in the list

  if(tail == nullptr){
    head = nullptr;
  }else{
    tail->next = nullptr;
  }

  delete del_linked;
  n_elements--;
}

/**
 * @brief push_back(const T & x): insert the element at the back of the list
 * 
 * @tparam T 
 * @param x value of element to be pushed
 */
template <typename T>
void simple_linked_list<T>::push_back(const T & x) {
  linked_node<T> *new_linked = new linked_node<T>(x);

  //new_linked->next = head;
  if(empty()){
    head = new_linked;
    //tail = new_node;
  }else{
    tail->next = new_linked;
    //tail = new_node;
  }
  tail = new_linked;
  n_elements++;

}

/**
 * @brief Destroy any new object that have just been created
 * 
 * @tparam T 
 */
template <typename T>
simple_linked_list<T>::~simple_linked_list() {
  clear();
}

/**
 * @brief size(): return the current elements in the list
 * 
 * @tparam T 
 * @return size_t 
 */
template <class T>
size_t simple_linked_list<T>::size() const {
  return n_elements;
}

/**
 * @brief clear(): remove all of nodes from the linked list to reset it to an empty state
 * 
 * @tparam T 
 */
template <typename T>
void simple_linked_list<T>::clear() {
  while(n_elements!= 0){
    pop_back();
  }
}

// IMPLEMENTATIONS FOR ITERATOR
/**
 * @brief comparison operator to check if it is pointing to the same node
 * 
 * @tparam T 
 * @param other 
 * @return true 
 * @return false 
 */
template <typename T>
bool simple_linked_iterator<T>::operator == (const simple_linked_iterator <T> & other) const {
  if(pos == other.pos){
    return true;
  }
  return false;
}

/**
 * @brief preincrement: called with iterator is incremented, it changes the current iterator so it points to the next node
 * 
 * @tparam T 
 * @return current iterator at new position
 */
template <typename T>
simple_linked_iterator <T> & simple_linked_iterator <T>::operator ++ () { // preincrement
  if(pos){
    pos = pos->next;
  }
  return *this;
}

/**
 * @brief post increment: changes the current iterator so it point to the next node
 * 
 * @tparam T 
 * @return return another iterator that points to the original node position
 */
template <typename T>
simple_linked_iterator <T> simple_linked_iterator<T>::operator ++ (int) { // postincrement
  simple_linked_iterator<T> temp = *this; //assign the current value to temp
    pos = pos->next;
  return temp;
}
    
/**
 * @brief dereference function
 * 
 * @tparam T 
 * @return return a reference to the 'data' member of the 'linked_node' that current iterator points to
 */
template <typename T>
T & simple_linked_iterator<T>::operator * () { // dereference operator
  return pos->data;
}

#endif

