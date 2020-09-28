#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"
#include "Path.h"
using namespace std;
class Path;
class Node;
class Graph{
    vector<Node*> Nodes;
    void getChild(int,vector<int>&);
    Path getMinWay(int begin, int end);
    Path getMaxWay(int begin, int end);
public:
    Graph(vector<vector<int>>);
    ~Graph();
    Node * getNode(int position){return Nodes[position];};
    Path GetWay(int begin , int end ,bool Lenght);
    bool pathExist(int,int);
};

#endif // !GRAPH_H
