/*
 * Purpose: the graph header file that defines all variables and functions
 */
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include "Node.hpp"
#include <unordered_map>
using namespace std;
/*
 * Class name: Graph
 * Purpose: the graph class declearation for member variables and functions
 * protected field: unordered_map<int, Node*> the Graph;
 * public field: constructor, destructor, loadFromFile, pathfinder, socialgathering
 * 		 printPath, getNode
 */
class Graph {
 protected:
  /*the hash map to store nodes for users*/
  unordered_map<int, Node *> theGraph;
  vector<Node*> vertices; 

 public:
  Graph(void);

  ~Graph(void);
  bool loadFromFile2(const char* in_filename);

  bool pathfinder(Node* from, Node* to);

  vector<int> printPath(Node* from, Node* to);
  
  Node* getNode(int i);
 
};

#endif  // GRAPH_HPP
