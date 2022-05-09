#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

void add(Node* &node, Node* &parent, Node* &head, int num);
void print(Node* node, int depth);
bool check(Node* node);
void fixer(Node* &node, Node* &head);


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
      
      add(child, head, head, x); // work on add
      
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

void add(Node* &parent, Node* &node, Node* &head, int num){

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
       

}

void fixer(Node* &node, Node* &head){
  
  Node* uncle;
  
  if (node->parent == NULL){

    cout << "gets here" << endl;

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

    cout << "gets here" << endl;

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
