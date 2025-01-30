/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include "split.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{ 
  // makes linked list 0 1 2 3 4 5
  Node* prev = nullptr;
  Node* curr = nullptr;
  for(int i = 5; i >= 0; i--) {
    curr = new Node(i, prev);
    prev = curr;
  }
  Node* odds = nullptr;
  Node* evens = nullptr;

  cout << "In: " << endl;
  Node* temp = curr;
  while(temp!= nullptr){
    cout << temp->value << " ";
    temp = temp->next;
  }
  cout << endl;

  split(curr, odds, evens);

  cout << "Odds: " << endl;
  Node* tempO = odds;
  while(tempO!= nullptr){
    cout << tempO->value << " ";
    tempO = tempO->next;
  }
  cout << endl;

  cout << "Evens: " << endl;
  Node* tempE = evens;
  while(tempE!= nullptr){
    cout << tempE->value <<" ";
    tempE = tempE-> next;
  }
  cout << endl;

  // cleanup
  while(odds!=nullptr){
    Node* del = odds;
    odds = odds->next;
    delete del;
  }

  while(evens!=nullptr){
    Node* del = evens;
    evens = evens->next;
    delete del;
  }
}
