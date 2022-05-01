#include <iostream>
#include <cstring>

using namespace std;

struct Node {

  int data;
  bool isred = true;
  
  Node* parent;
  Node* right = NULL;
  Node* left = NULL;

};
