// Red Black Tree
// An auto-balancing binary tree, using specific rules and colors to balance
// completed by Ehan Masud
// with help from Nathan Zou and the resource page provided on canvas

#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;

void add(Node* &node, Node* &parent, Node* &head, int num);
void print(Node* node, int depth);
bool check(Node* node);
void fixer(Node* &node, Node* &head);
void deleter(int num, Node* &child, Node* &parent);


int main(){

  char input[100];
  bool stillgoing = true;
  Node* head = NULL;
  Node* child = NULL;
  int x;
  
  cout << "Welcome to Red Black Tree!" << endl;

  while (stillgoing == true){
    
    cout << "What would you like to do? (ADD, READ, PRINT, DELETE, QUIT)" << endl;
    
    cin >> input;

    if (strcmp(input, "ADD") == 0){

      cout << "What number are you adding?" << endl;

      cin >> x;
      
      add(child, head, head, x); // add
      
    }

    if (strcmp(input, "READ") == 0){ // reads in file and inputs it

      char numberfile[1000];
      
      cout << "What is the name of the file?" << endl;

      cin >> numberfile;

      ifstream input_file(numberfile);

      if (!input_file.is_open()){

	cout << "could not open this file" << endl;

      }
      while (!input_file.eof()) {

	int num;
	input_file >> num;
	add(child, head, head, num);
	
      }

      input_file.close();
      
    }

    if (strcmp(input, "DELETE") == 0){

      int p;
      cout << "What would you like to delete?" << endl;

      cin >> p;

      deleter(p, head, head->parent);
      
    }
    
    if (strcmp(input, "PRINT") == 0){ // prints

      print(head, 0);
      
    }
    
    if (strcmp(input, "QUIT") == 0){ // quits

      stillgoing = false;
      break;

    }

  }

}

void add(Node* &parent, Node* &node, Node* &head, int num){ // similar to bst but with colors as well

  if (node == NULL){

    Node* temp = new Node();
    
    if (parent == NULL){
      temp->isred = false;
      temp->data = num;
      node = temp;
      return;
    }
    else{

      temp->data = num;
      temp->parent = parent;
      node = temp;

      if (check(node) == true){

	// cases start

	fixer(node, head);

      }
      
      return;
      
    }

  }

  else {

    if (num > node->data){

      add(node, node->right, head, num);

    }
    else{

      add(node, node->left, head, num);

    }

  }
  

}

void print(Node* node, int depth){ // same print system as bst, but uses B and R as color indicators

   if (node == NULL){

    cout << "tree is empty!" << endl;
    return;
    
  }
  
  if (node->right != NULL){

    print(node->right, depth + 1);
    
  }

  for (int i = 0; i < depth; i++){

    cout << "\t";
    
  }

  if (node->isred == false){

    cout << "B " << endl;

  }
  else{

    cout << "R " << endl;

  }

  for (int i = 0; i < depth; i++){

    cout << "\t";

  }

  
  cout << node->data << endl;

  if (node->left != NULL){

    print(node->left, depth + 1);

  }


  
}

bool check(Node* node){ // checks if parent and node are both red or not

  if (node->parent == NULL){

    return true;

  }
  
  if (node->parent->isred == true){

    if (node->isred == true){

      return true;

    }

  }

  else {

    return false;

  }

  return false;
       

}

void fixer(Node* &node, Node* &head){ // balances and fixes issues if check() runs true
  
  Node* uncle;
  
  if (node->parent == NULL){

    node->isred = false;
    return;
    
  }
  
  Node* grandpa = node->parent->parent;
  
  if (node->parent == grandpa->right){
  
    uncle = grandpa->left;

  }
  else{

    uncle = grandpa->right;
    
  }

  // case 4
  
  if (uncle == NULL){
    
    Node* first = node;
    Node* second = node->parent;
    Node* third = grandpa;

    Node* newnode = new Node(); 
    
    if (node->parent == grandpa->left){

      if (node->data > node->parent->data){
	
	grandpa->right = newnode;
	newnode->parent = grandpa;
	newnode->data = third->data;
	third->data = first->data;
	node = NULL;
	return;
	
      }
      else {

	grandpa->right = newnode;
	newnode->parent = grandpa;
	newnode->data = third->data;
	third->data = second->data;
	second->data = first->data;
	node = NULL;
	return;

      }
      
    }
    else {

      if (node->data > node->parent->data){

	grandpa->left = newnode;
	newnode->parent = grandpa;
	newnode->data = third->data;
	third->data = second->data;
	second->data = first->data;
	node = NULL;
	return;

      }
      else{

	grandpa->left = newnode;
	newnode->parent = grandpa;
	newnode->data = third->data;
	third->data = first->data;
	node = NULL;
	return;
	

      }


    }
    
  }

  // case 3
  
  else if (uncle->isred == true && node->parent->isred == true){
  
    node->parent->isred = false;
  
    if (uncle->isred == true){

      uncle->isred = false;

    }

    grandpa->isred = true;

    if (check(grandpa) == true){

      fixer(grandpa, head);

    }

  }

  // case 5
  
  else if (uncle != NULL && uncle->isred != true && node->parent->isred == true){
    
    if (node->parent->data > grandpa->data){
      if (node->data > node->parent->data){

	node->parent->left->parent = grandpa;
	grandpa->right = node->parent->left;
	grandpa->parent = node->parent;
	node->parent->parent = NULL;
	node->parent->left = grandpa;

	head = node->parent;
	node->parent->isred = false;
	node->parent->left->isred = true;
	node->parent->right->isred = true;
	return;

      }
    

      else if (node->data < node->parent->data){

	node->parent->left = node->right;
	node->parent->parent = node;
	node->right = node->parent;
	grandpa->right = node->left;
	grandpa->parent = node;
	node->left = grandpa;
	node->parent = NULL;
	head = node;

	node->left->isred = true;
	node->right->isred = true;
	node->isred = false;
	return;

      }

    }

    else {

      if (node->data < node->parent->data){

	grandpa->parent = node->parent;
	grandpa->left = node->parent->right;
	node->parent->right = grandpa;
	node->parent->parent = NULL;
	head = node->parent;

	node->parent->isred = false;
	node->parent->left->isred = true;
	node->parent->right->isred = true;
	return;

      }

      else if (node->data > node->parent->data){

	node->parent->right = node->left;
	node->left = node->parent;
	node->parent->parent = node;
	grandpa->left = node->right;
	node->right->parent = grandpa;
	grandpa->parent = node;
	node->right = grandpa;

	head = node;
	node->isred = false;
	node->left->isred = true;
	node->right->isred = true;
	return;


      }


    }

  }


}

void deleter(int num, Node* &child, Node* &parent){

  if (child == NULL){

    cout << "no number to delete!" << endl;
    return;

  }
  
  if (child->data < num){

    deleter(num, child->right, child);

  }

  else if (child->data > num){

    deleter(num, child->left, child);

  }

  else if (child->data == num) {

    //case 0: // delete head

    if (parent == NULL){

      if (child->left == NULL && child->right == NULL){
	child = NULL;
	return;
      }

      else {

	if (child->left != NULL){

	  Node* temp;
	  Node* temp2;

	  temp = child->left;
	  temp2 = child->left->right;
	  
	  while (temp2 != NULL){

	    temp = temp2;
	    temp2 = temp2->right;
	    
	  }

	  child->data = temp->data;
	  if (temp->parent->parent == NULL){
	    temp->parent->left = NULL;
	  }
	  else {
	    temp->parent->right = NULL;
	  }
	  temp = NULL;
	  return;

	}

	else {

	  Node* temp;
	  Node* temp2;

	  temp = child->right;
	  temp2 = child->right->left;

	  while (temp2 != NULL){

	    temp = temp2;
	    temp2 = temp2->left;

	  }

	  child->data = temp->data;
	  if (temp->parent->parent == NULL){
	    temp->parent->right = NULL;
	  }
	  else {
	    temp->parent->left = NULL;
	  }
	  temp = NULL;
	  return;

	}

      }

    }
    
    //case 1: leaf

    if (child == parent->left){

      parent->left = NULL;
      return;
      
    }

    if (child == parent->right){

      parent->right = NULL;
      return;
      
    }

  }

  else {

    cout << "no number to delete!" << endl;

  }


}
