/*
 * Name: Yifeng Hua
 * UserId: cs100wgc
 * Programming Assignment 3
 * Data: March 4
 * Purpose: the node head file that includes members of a node object
 * Source of Help: none
 */
#ifndef NODE_HPP
#define NODE_HPP


#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

/*
 * Class Name: Node
 * Purpose: node class that contains the definitation of all member variables
 */
class Node{

  public:
    vector<int> adj;
    bool visited;
    int dist;
    int index;
    int prev;
    int degree;
    int core;
    bool invite;
    unordered_map<int,int> distMap; 
  //public:

    Node(){}
    ~Node(){}
};

#endif
