/*
 * Purpose: the graph file that can form an undirected and weighted graph and
 *          could find a shortest path between two specific IDs.
 */
#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>
#include "Node.hpp"
#include <queue>
#include <list>
#include <iterator>
using namespace std;
#define TWO 2
#define THREE 3
#define SPACE ' '
#define NONEXIST NULL
#define STRING "Failed to read "
#define STRING2 "!\n"

/* Function Name: Graph
 * Parameter: void
 * Return: none
 * Purpose: constructor of Graph object and initialize the theGraph
 */
Graph::Graph(void)
    : theGraph(0) {}

/* Function Name: ~Graph
 * Parameter: void
 * Return: none
 * Purpose: destructor to delete all the nodes created on heap
 */
Graph::~Graph(void) {
  /*iterate the unordered map*/
  for (auto itr = theGraph.begin(); itr != theGraph.end(); itr++) {
    delete itr->second;
  }
}

/*
 * Function Name: loadFromFile2
 * Parameter: const char* in_filename
 * Return: bool
 * Purpose: read from the input file and process line by line.
 *          Create nodes for the each ID and assign the member
 *          variables according, seting up the weighted graph.
 */
bool Graph::loadFromFile2(const char* in_filename){
  
  ifstream infile(in_filename);
  
  /*while loop to read the file*/
  while(infile) {
    string s;
    /*EOF check*/
    if (!getline(infile, s)) break;
    istringstream ss(s);
    vector<string> record;

    /*while loop to process one line*/
    while(ss){
      string s;
      if(!getline(ss, s, SPACE))break;
      record.push_back(s);
    }
    
    /*if not found exactly three infos*/
    if (record.size() != THREE){
	continue;
    }

    /*turn the string in to integer*/
    int from = stoi(record[0]);
    int end = stoi(record[1]);
    int weight = stoi(record[TWO]);

    /*create the node for the first ID*/
    if (theGraph.find(from) == theGraph.end()){
      Node* newNode = new Node();
      newNode -> index = from;
      theGraph[from] = newNode;
    }

    /*create the node for the second ID*/
    if (theGraph.find(end) == theGraph.end()){
      Node* newNode2 = new Node();
      newNode2 -> index = end;
      theGraph[end] = newNode2;
    }

    /*Create the undirected relationship*/
    theGraph.at(from) -> adj.push_back(end);
    theGraph.at(end) -> adj.push_back (from);

    /*add the weight by unordered map*/
    theGraph.at(from)->distMap[end] = weight;
    theGraph.at(end)->distMap[from] = weight;
  }

  /*error info*/
  if (!infile.eof()){
      cerr<<STRING<<in_filename<<STRING2;
      return false;
  }
  infile.close();
  return true;
} 

/*
 * Function Name: pathfinder
 * Parameter: Node* from, Node* to
 * Return : bool
 * Purpose: find the shortest path between two nodes
 */
bool Graph::pathfinder(Node* from, Node* to) {
  
  /*for loop to go through the nodes*/
  for (auto n : theGraph){
    
    /*pre process the nodes*/
    (n.second) -> visited = false;
    (n.second) -> prev = -1;
    (n.second) -> dist = std::numeric_limits<int>::max();
  }

  priority_queue<pair<int,int>,vector<pair<int,int>>, 
 	        greater<pair<int,int>>> toExplore;
  /*set the first node and set up the queue*/
  from->dist = 0;
  toExplore.push(make_pair(0, from->index));

  /*while loop until queue is empty*/
  while (!toExplore.empty()){
    int currentInt = toExplore.top().second;
    Node* current = theGraph.at(currentInt);
    toExplore.pop();
    
    /*check if the node is visited*/
    if (current -> visited == false){
      current -> visited = true;

    /*for loop to go through adj*/
    for (int n : current->adj){ 
      int distance = current->dist + current->distMap[n];
      Node* nNode = getNode(n);
      /*process if the node is not visted yet*/
      if (distance < nNode -> dist){
 	
	/*adjust the prev and dist,and enqueue*/
        nNode -> prev = current->index;
        nNode -> dist = distance;
	toExplore.push(make_pair(distance,n));
      
      }
     }
    }
  }
  return true;
}

/*
 * Function Name: printPath
 * Paramter: Node* from, Node* to
 * Return: vector<int> Graph
 * Purpose: Read the shortest path and store to vector
 */
vector<int> Graph::printPath(Node* from, Node*to){

  
  vector<int> copy;
  /*edge case for same nodes*/
  if (from == to){
    copy.push_back(from->index);
    return copy;
  }

  /*edge case for not found*/
  if (pathfinder(from, to) != true)
    return copy;
  
  /*create a copy of the to node*/
  Node*end = to;
  copy.push_back(end->index);

  /*while loop to put path to copy*/
  while(true){
    if (end->prev == -1)
      break;
    copy.push_back(end->prev);
    end = theGraph.at(end->prev);
  }
  return copy;
}

/*
 * Function Name: getNode
 * Paramter: int i
 * Return: Node*
 * Purpose: get the node if provided id
 */
Node* Graph::getNode (int i){
   /*check if node exists*/
 if (theGraph.find(i) == theGraph.end())
   return NONEXIST;
 return theGraph.at(i);
}


