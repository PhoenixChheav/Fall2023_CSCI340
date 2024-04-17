/**********************************************************************************************
 * NIU CSCI 340 Section 0003                                                                  *
 * Assignment 6                                                                               *
 * Phoenix Chheav - Z1966108 - phoenixchh                                                     *
 *                                                                                            *
 *   I certify that everything I am submitting is either provided by the professor for use in *
 * the assignment, or work done by me personally. I understand that if I am caught submitting *
 * the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic    *
 * Misconduct and will be punished as such.                                                   *
 *                                                                                            *
 **********************************************************************************************/
#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include "bintree.decl.h"

#include <vector>
#include <queue>

/**
 * @brief This method is binary tree preorder traversal.
 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root root of the tree to traverse.
 * @param fn a function or function-like object that is called to visit each node during the traversal.
 */
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
  if(root == nullptr){
    return;
  }

  fn(root);
  preorder(root->left, fn);
  preorder(root->right, fn);
}

/**
 * @brief This method is binary tree inorder traversal.
 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root root of the tree to traverse.
 * @param fn a function or function-like object that is called to visit each node during the traversal.
 */
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
  if(root == nullptr){
    return;
  }

  inorder(root->left, fn);
  fn(root);
  inorder(root->right, fn);
}

/**
 * @brief This method is binary tree postorder traversal.
 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root root of the tree to traverse.
 * @param fn a function or function-like object that is called to visit each node during the traversal.
 */
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
  if(root == nullptr){
    return;
  }

  postorder(root->left, fn);
  postorder(root->right, fn);
  fn(root);
}

/**
 * @brief This method is binary tree levelorder traversal.
 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root root of the tree to traverse
 * @param fn a function or function-like object that is called to visit eache node during the traversal.
 */
template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) {
  if(root == nullptr){
    return;
  }

  std::queue<BINTREENODE*> q;
  q.push(root);

  while(!q.empty()){
    BINTREENODE *node = q.front();
    q.pop();
    fn(node);

    if(node->left != nullptr){
      q.push(node->left);
    }

    if(node->right != nullptr){
      q.push(node->right);
    }
  }
}

/**
 * @brief This is title_get_children method.
 * 
 * @param node the node whos children we would like to gather.
 * @return return all of the direct children of the given node.
 */
template <typename BINTREENODE>
std::vector <BINTREENODE *> tilted_get_children(BINTREENODE * node) {
  std::vector<BINTREENODE*> children;
  if(node == nullptr){
    return {};
  }

  BINTREENODE *current = node->left;
    //add left child of current node is not empty, add it to children then add right node
  while(current != nullptr){
    children.push_back(current);
    current = current->right;
  }
  
  return children; 
}

/**
 * @brief this method will be called to find the real parent of the current node.
 * 
 * @param node 
 * @return return pointer to the node that is the real parent of the current node.
 */
// this function requires that BINTREENODE have the parent member
template <typename BINTREENODE>
BINTREENODE * tilted_find_parent(BINTREENODE *node) {
  if(node == nullptr || node->parent == nullptr){
    return nullptr;
  }

  //parent in bintree is also the parent of original tree.
  if(node->parent == nullptr || node->parent->left == node){
    return node->parent;
  }
  //if not, follow left pointer to find the real parent.
  return tilted_find_parent(node->parent);
}

/**
 * @brief This function performs a level order traversal of the non-binary tree that was tilted to create the binary tree with root `root`.
 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root the root of the tree to traverse.
 * @param fn The function or function-like object to be called with the current node when visiting.
 */
template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn) {
  if(root == nullptr){
    return;
  }

  std::queue<BINTREENODE*> q;
  q.push(root);

  while(!q.empty()){
    //int level_size = q.size();

    BINTREENODE *current = q.front();
    q.pop();

    fn(current);//apply fn to node

    std::vector<BINTREENODE *> children = tilted_get_children(current);
    for(BINTREENODE *child : children){
      q.push(child);
    }
  }
}

/**
 * @brief This method will be called to delete a binary tree.
 * 
 * @tparam BINTREENODE 
 * @param node node that will be deleted.
 */
template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node) {
  if(node == nullptr){
    return;
  }

  delete_tree(node->left);
  delete_tree(node->right);
  delete node;
  node = nullptr;
}

#endif

