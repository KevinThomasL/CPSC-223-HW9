
//----------------------------------------------------------------------
// Author: Kevin Lunden
// Course: CPSC 223, Spring 2020
// Assign: 9
// File:   bst_collection.h
//----------------------------------------------------------------------



#ifndef BST_COLLECTION_H
#define BST_COLLECTION_H

#include <vector>
#include <algorithm>           
#include "collection.h"


template<typename K, typename V>
class BSTCollection : public Collection<K,V>
{
public:

  // create an empty tree
  BSTCollection();
  
  // bst copy constructor
  BSTCollection(const BSTCollection <K,V>& rhs);

  // bst assignment operator
  BSTCollection<K,V>& operator=(const BSTCollection <K ,V >& rhs);

  // delete the bst
  ~BSTCollection();
  
  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

  // return the height of the tree
  int height() const;
  
private:

  // tree node structure
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  // helper to empty entire tree
  void make_empty(Node* subtree_root);
  
  // helper to calc tree height (can use std::max)
  int height(const Node* subtree_root) const;

  // helper to build sorted list of keys (used by keys and sort)
  void inorder(const Node* subtree_root, std::vector<K>& keys) const;

  // helper to recursively find range of keys
  void range_search(const Node* subtree_root, const K& k1, const K& k2,
                    std::vector<V>& vals) const;

  // recursively (deep) copy ancestors of src to dst
  void preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst);

  // helper function to remove a node recursively
  Node* remove(const K& key, Node* subtree_root);
  
  // number of k-v pairs in the collection
  int collection_size; 

  // tree root
  Node* root; 
};


// TODO: implement the above functions here ...
template<typename K, typename V>
BSTCollection<K,V>::BSTCollection() : collection_size(0), root(nullptr){}

template<typename K, typename V>
BSTCollection<K,V>::BSTCollection(const BSTCollection<K,V>& rhs)
  : collection_size(0), root(nullptr)
{
  *this = rhs;
}

template<typename K, typename V>
BSTCollection<K,V>& BSTCollection<K,V>::operator=(const BSTCollection<K,V>& rhs)
{
 if (this == &rhs) 
 {
  return *this;
 }
 // delete current
 make_empty(root);
 // build tree
 std::vector<K> keys;
 //preorder_copy(root, rhs.root);
 int val = 0;
 for(int i = 0; i < rhs.collection_size; i++)
 {
  rhs.find(keys[i], val);
  add(keys[i], val);
 }
 return *this;
}

template<typename K, typename V>
BSTCollection<K,V>::~BSTCollection()
{
  make_empty(root);
}

// add a new key-value pair into the collection
template<typename K, typename V>
void BSTCollection<K,V>::add(const K& a_key, const V& a_val)
{
  //create node and set children to nullptr
  Node* tree = new Node;
  tree->key = a_key;
  tree->value = a_val;
  tree->left = nullptr;
  tree->right = nullptr;

  //if no root
  if(root == nullptr)
  {
   root = tree;
   tree->left = nullptr;
   tree->right = nullptr;
  }
  else
  {
   Node* cur = new Node;
   cur = root;
   while (cur != nullptr)
   {
    if(tree->key < cur->key)
    {
        if(cur->left == nullptr)
	{
         cur->left = tree;
         cur = nullptr;
        }
	else
	{
         cur = cur->left;
        }
    }
    else
    {
     if(cur->right == nullptr)
     {
      cur->right = tree;
      cur = nullptr;
     }
     else
     {
      cur = cur->right;
      tree->left = nullptr;
      tree->right = nullptr;
     }
    }
   }
  }
 //add to size of tree
 collection_size++;
}

// remove a key-value pair from the collection
template<typename K, typename V>
void BSTCollection<K,V>::remove(const K& a_key)
{
  root = remove(a_key, root);
}

// helper function to remove a node recursively
template<typename K, typename V>
typename BSTCollection<K,V>::Node* BSTCollection<K,V>::
remove(const K& a_key, Node* subtree_root)
{
 //if no subtree
 if(subtree_root == nullptr)
 {
  return subtree_root;
 } 
 else if(subtree_root && a_key < subtree_root->key)
 {
  subtree_root->left = remove(a_key, subtree_root->left);
 }
 else if(subtree_root && a_key > subtree_root->key)
 {
  subtree_root->right = remove(a_key, subtree_root->right);
 } 
 else if(subtree_root && a_key == subtree_root->key)
 {
  Node* tree = subtree_root;
  //if no children
  if(subtree_root->left == nullptr && subtree_root->right == nullptr)
  {
   delete tree;
   subtree_root = nullptr;
   collection_size--;
  } 
  else if(subtree_root->left != nullptr && subtree_root->right == nullptr)
  {
   subtree_root = subtree_root->left;
   delete tree;
   tree = nullptr;
   collection_size--;
  } 
  else if(subtree_root->right != nullptr && subtree_root->left == nullptr)
  {
   subtree_root = subtree_root->right;
   delete tree;
   tree = nullptr;
   collection_size--;
  } 
  else
  {
   Node* prev = subtree_root;
   tree = subtree_root->right;
   while(tree->left != nullptr)
   {
    prev = tree;
    tree = tree->left;
   }
   if(prev != subtree_root)
   {
    prev->left = tree->right;
   }
   tree->left = subtree_root->left;
   if(subtree_root->right != tree)
   {
    tree->right = subtree_root->right;
   }
   //remove and reset values
   delete subtree_root;
   subtree_root = tree;
   prev = nullptr;
   tree = nullptr;
   collection_size--;
  }
 }
 return subtree_root;
}

// find and return the value associated with the key
template<typename K, typename V>
bool BSTCollection<K,V>::find(const K& search_key, V& the_val) const
{
 Node* tree = root;
 while(tree != nullptr)
 {
  //if correct node return value otherwise search left or right
  if(tree->key == search_key)
  {
   the_val = tree->value;
   return true;
  }
  else if(search_key < tree->key)
  {
   tree = tree->left;
  } 
  else
  {
   tree = tree->right;
  }
 }
 return false;
}

// find and return the values with keys >= to k1 and <= to k2
template<typename K, typename V>
void BSTCollection<K,V>::find(const K& k1, const K& k2,std::vector<V>& vals) const
{
 range_search(root, k1, k2, vals);
}

// helper to recursively find range of keys
template<typename K, typename V>
void BSTCollection<K,V>::range_search(const Node* subtree, const K& k1, const K& k2, std::vector<V>& vals)
const 
{
 // use as recursive helper function
 if(subtree == nullptr)
  return;
  
 range_search(subtree->left, k1, k2, vals);

 if(k1 <= subtree->key && k2 >= subtree->key)
  vals.push_back(subtree->value);

 range_search(subtree->right, k1, k2, vals);
}

// return all of the keys in the collection
template<typename K, typename V>
void BSTCollection<K,V>::keys(std::vector<K>& all_keys) const
{
 inorder(root, all_keys);
}

// return all of the keys in ascending (sorted) order
template<typename K, typename V>
void BSTCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
 inorder(root, all_keys_sorted);
}

// return the number of key-value pairs in the collection
template<typename K, typename V>
int BSTCollection<K,V>::size() const
{
 return collection_size;
}

// helper to calc tree height (can use std::max)
template<typename K, typename V>
int BSTCollection<K,V>::height(const Node* subtree_root) const
{
 if(subtree_root == nullptr)
  return 0;

 int left = height(subtree_root->left);
 int right = height(subtree_root->right);

 if(left > right)
  return(left+1);
 else
  return(right+1);
}

// helper to empty entire tree
template<typename K, typename V>
void BSTCollection<K,V>::make_empty(Node* subtree_root) 
{
  if(subtree_root == nullptr)
    return;

  make_empty(subtree_root->left);
  make_empty(subtree_root->right);
  subtree_root == nullptr;
}

// helper to build sorted list of keys (used by keys and sort)
template<typename K, typename V>
void BSTCollection<K,V>::inorder(const Node* subtree_root, std::vector<K>& keys) const
{
  // recursive helper function
  if(subtree_root == nullptr)
    return;

  inorder(subtree_root->left, keys);
  keys.push_back(subtree_root->key);
  inorder(subtree_root->right, keys);
}

// recursively (deep) copy ancestors of src to dst
template<typename K, typename V>
void BSTCollection<K,V>::preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst)
{
 if (subtree_root_src == nullptr)
  subtree_root_dst = nullptr;
 else
 { 
  subtree_root_dst = subtree_root_src;

  preorder_copy(subtree_root_src->left, subtree_root_dst->left);
  preorder_copy(subtree_root_src->right, subtree_root_dst->right);
 } 
}

// return the height of the tree
template<typename K, typename V>
int BSTCollection<K,V>::height() const
{
  return height(root);
}

#endif
