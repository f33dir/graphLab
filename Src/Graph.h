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
    Path getMaxWay(int begin, int end,vector<Node*>,Path);
public:
    template<class t>
    bool isIn(vector<t> vec,t item){
        return find(vec.begin(),vec.end(),item)!=vec.end();
    }
    Graph(vector<vector<int>>);
    bool operator=(const Graph&);
    ~Graph();
    Node * getNode(int position){return Nodes[position];};
    Node * getNode(int position,vector<Node *>vec ){return vec[position];};
    Path GetWay(int begin , int end ,bool Lenght);
    bool pathExist(int,int);
};

#endif // !GRAPH_H
