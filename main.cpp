#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

void add(Node* &node, Node* &parent, int num);
void print(Node* node, int depth);
bool check(Node* node);
void fixer(Node* &node);


int main(){

  char input[100];
  bool stillgoing = true;
  Node* head = NULL;
  Node* child = NULL;
  int x;
  
  cout << "Welcome to Red Black Tree!" << endl;

  while (stillgoing == true){
    
    cout << "What would you like to do? (ADD, READ, PRINT, QUIT)" << endl;
    
    cin >> input;

    if (strcmp(input, "ADD") == 0){

      cout << "What number are you adding?" << endl;

      cin >> x;
      
      add(child, head, x); // work on add
      
    }

    if (strcmp(input, "READ") == 0){

      cout << "read function" << endl;
      
    }
    
    if (strcmp(input, "PRINT") == 0){

      print(head, 0);
      
    }
    
    if (strcmp(input, "QUIT") == 0){

      stillgoing = false;
      break;

    }

  }

}

void add(Node* &parent, Node* &node, int num){

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

	fixer(node);

      }

      else {

	cout << "no oopsie" << endl;

      }
      
      return;
      
    }

  }

  else {

    if (num > node->data){

      add(node, node->right, num);

    }
    else{

      add(node, node->left, num);

    }

  }
  

}

void print(Node* node, int depth){

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

bool check(Node* node){

  if (node->parent->isred == true){

    if (node->isred == true){

      return true;

    }

  }

  else {

    return false;

  }
       

}

void fixer(Node* &node){

  Node* uncle;
  
  if (node->parent == NULL){

    node->isred = false;
    return;
    
  }
  
  Node* grandpa = node->parent->parent;

  if(node->parent == grandpa->right){
  
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

    cout << "gets here" << endl;
    
    if (node->parent == grandpa->left){

      if (node->data > node->parent->data){
	
	grandpa->right = newnode;
	newnode->data = third->data;
	third->data = first->data;
	node = NULL;
	return;
	
      }
      else {

	grandpa->right = newnode;
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
	newnode->data = third->data;
	third->data = second->data;
	second->data = first->data;
	node = NULL;
	return;

      }
      else{

	grandpa->left = newnode;
	newnode->data = third->data;
	third->data = first->data;
	node = NULL;
	return;
	

      }


    }
    
  }

  // case 3
  
  if (uncle->isred == true && node->parent->isred == true){
  
    node->parent->isred = false;
  
    if (uncle->isred == true){

      uncle->isred = false;

    }

    fixer(grandpa);

  }


}
