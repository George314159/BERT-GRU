/*
 * Name: Yifeng Hua
 * UserId: cs100wgc
 * Programming Assignment 3
 * File: pathfinder.c
 * Date: March 4
 * Purpose: launch the pathfinder program , handle the parameters from command
 * line, and call the functions in the Graph.cpp. The whole program will 
 * create an undirected and weighted graph for user IDs and find shortest 
 * path between two specific users, and output the path to a new file.
 * Source of Help: none
 */
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include "Node.hpp"
#include <stack>

using namespace std;
#define SPACE " "
#define ARGC 4
#define TWO 2
#define THREE 3
#define NONEXIST NULL
#define WHITE ' '
#define INCORRECT " called with incorrect arguments."
#define USAGE "USAGE: "
#define STRING " friendship_pairs_file test_pairs_file output_file"

/*
 * Function Name: usage
 * Parameter: char* pragram_name
 * Purpose: called if the arguments from command line are incorrect, 
 *          print usage info.
 * Return: void
 */
void usage(char* program_name) {
  cerr << program_name << INCORRECT << endl;
  cerr << USAGE << program_name
       << STRING
       << endl;
  exit(-1);
}

/*
 * Function Name: main
 * Parameter: int argc, char* argv[]
 * Purpose: launch the whole program, creating a Graph object and pass the 
 *          input file to load from file function in Graph.cpp, and call 
 *          the print path function to find the shortest path between two 
 *          users one by one, and write to the file.
 * Return: int
 */
int main(int argc, char* argv[]) {
  
  /*check the arguments*/
  if (argc != ARGC) {
    usage(argv[0]);
  }
  
  /*Get the file names*/
  char* graph_filename = argv[1];
  char* pairs_filename = argv[TWO];
  char* output_filename = argv[THREE];

  /*Create a graph object and load files*/
  Graph graph;
  graph.loadFromFile2(graph_filename);

  /*create ifstream and ofstream*/
  ifstream infile(pairs_filename);
  ofstream os;
  os.open(output_filename);

  /*while loop to get the two user IDS*/
  while(infile){

  /*read one line from the file*/
  string s;
  if (!getline(infile, s)) break;
  istringstream ss(s);
  vector<string> record;
   
  /*split the integers by space*/ 
  while (ss) {
    string s;
    if (!getline(ss,s,WHITE)) break;
    record.push_back(s);
  }

  /*continue to read until found two IDs*/
  if (record.size() != TWO) {
    continue;
  }

  int from = stoi(record[0]);
  int end = stoi(record[1]);

  /*get the node for passing*/
  Node* fromNode = graph.getNode(from);
  Node* endNode = graph.getNode(end);
  
  /*check if node is null*/   
  if (fromNode == NONEXIST || endNode == NONEXIST){
    os << endl;
    continue;
  } 

  /*call printPath to get the paths*/
  vector<int> shortest;     	
  shortest = graph.printPath(fromNode, endNode);
 
  /*for loop to write paths on file*/
  for (int i = shortest.size() - 1; i >= 0; i--){
     os << shortest[i];
     if (i != 0)
       os << SPACE;
     }
     os << endl;   
    }
  /*finish the program*/
  os.close();
  infile.close(); 
  return 1;
} 
