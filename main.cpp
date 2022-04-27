#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

void add(Node* node, int num);

int main(){

  char input[100];
  bool stillgoing = true;
  Node* head = NULL;
  int x;
  
  cout << "Welcome to Red Black Tree!" << endl;

  while (stillgoing == true){
    
    cout << "What would you like to do? (ADD, READ, PRINT, QUIT)" << endl;
    
    cin >> input;

    if (strcmp(input, "ADD") == 0){

      cout << "What number are you adding?" << endl;

      cin >> x;
      
      add(head, x); // work on add
      
    }

    if (strcmp(input, "READ") == 0){

      cout << "read function" << endl;
      
    }
    
    if (strcmp(input, "PRINT") == 0){

      cout << "print function" << endl;
      
    }
    
    if (strcmp(input, "QUIT") == 0){

      stillgoing = false;
      break;

    }

  }

}
