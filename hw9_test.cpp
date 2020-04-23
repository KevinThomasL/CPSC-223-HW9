//----------------------------------------------------------------------
// Author: Kevin Lunden
// Course: CPSC 223, Spring 2020
// Assign: 9
// File:   hw9_test.cpp
//
// TODO:   tests the functions of BTSCollection.h
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "bst_collection.h"

using namespace std;


// Test 1
TEST(BasicListTest, CorrectSize) {
  BSTCollection<string,double> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  ASSERT_EQ(3, c.size());

}

// Test 2
TEST(BasicListTest, SimpleFind) {
  BSTCollection<string,double> c;
  double v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10.0);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10.0, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20.0, v);
}

// Test 3
TEST(BasicListTest, SimpleRemoveElems) {
  BSTCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("b");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("b", v));  
  c.remove("c");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("c", v));  
  c.remove("d");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("d", v));  
}

// Test 4
TEST(BasicListTest, SimpleRange) {
  BSTCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(20, 40, vs);
  ASSERT_EQ(3, vs.size());
  // note that the following "find" is a C++ built-in function
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "e"));  
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "f"));  
}

// Test 5
TEST(BasicListTest, SimpleSort) {
  BSTCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(5, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}


// TODO: ... additional tests ...

// test 6
// tests sorting with bigger and negative numbers
TEST(BasicCollectionTest, DifficultSort) {
  BSTCollection<string,double> c;
  c.add("a", -10.0);
  c.add("b", 20.0);
  c.add("c", 30.0);
  c.add("d", 40.0);
  c.add("e", 500.0);
  vector<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(c.size(), sorted_keys.size());
  for (int i = 0; i < int(sorted_keys.size()) - 1; ++i) {
    ASSERT_LE(sorted_keys[i], sorted_keys[i+1]);
  }
}

//test 7
//checks removing nonexistent node doesn't impact tree
//checks removing parent and leaf nodes
TEST(BasicCollectionTest, DifficultRemoveElems){
  BSTCollection<char, int> c;
  ASSERT_EQ(c.height(), 0);
  ASSERT_EQ(c.size(), 0);
  c.add('d', 40);
  c.add('b', 20);
  c.add('e', 50);
  c.add('a', 10);
  c.add('c', 30);
  c.remove('z');
  ASSERT_EQ(c.height(), 3);
  ASSERT_EQ(c.size(), 5);
  double v;
  c.remove('b');          
  ASSERT_EQ(c.height(), 3);
  ASSERT_EQ(c.size(), 4); 
  c.remove('e');        
  ASSERT_EQ(c.height(), 3);
  ASSERT_EQ(c.size(), 3); 
}

// Test 8
// checks entire range working with larger and negative numbers
TEST(BasicListTest, DifficultRange) {
  BSTCollection<int,string> c;
  c.add(50, "e");
  c.add(-10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(600, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(-10, 600, vs);
  ASSERT_EQ(6, vs.size());
  // note that the following "find" is a C++ built-in function
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "e"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "f"));
}

// Test 9
// tests added and finding large and negative numbers
TEST(BasicListTest, DiificultFind) {
  BSTCollection<string,double> c;
  double v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 100.0);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(100.0, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", -20.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(-20.0, v);
  ASSERT_EQ(false, c.find("c", v));
  c.add("c", 10000.0);
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(10000.0, v);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

