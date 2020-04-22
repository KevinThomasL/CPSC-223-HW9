
//----------------------------------------------------------------------
// Author: ...
// Course: CPSC 223, Spring 2020
// Assign: 9
// File:   bst_collection.h
// ...
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

// Note that for the remove helper, since it returns a Node pointer,
// it must be defined as: 
//
//   template<typename K, typename V>
//   typename BSTCollection<K,V>::Node*
//   BSTCollection<K,V>::remove(const K& key, Node* subtree_root)
//   {
//     ...
//   }


#endif
