#include "Graph.h"
#include <stack>
#include <algorithm>
using namespace std;
Graph::Graph(vector<vector<int>> input ){
    for(int i = 0;i<input.size();i++){
        Node* node = new Node(i,input[i]);
        this->Nodes.push_back(node);
    }
}

Graph::~Graph(){
    for(auto node : Nodes){
        delete node;
    }
}


bool Graph::pathExist(int begin , int end){
    vector<int> visited;
    getChild(begin,visited);
    auto answer = (find(visited.begin(),visited.end(),end)!=visited.end());
    return answer;
}

void Graph::getChild(int current,vector<int> &visited){
    Node * currentNode = getNode(current);
    visited.push_back(currentNode->getId());
    for(auto next : currentNode->_out){
        if(find(visited.begin(),visited.end(),next)==visited.end()){
            getChild(next,visited);
        }
    }
};

Path Graph::GetWay(int begin,int end,bool lenght){
    Path output;
    if(pathExist(begin,end)){
        if(lenght){
            
        }
        else{
            output = getMinWay(begin,end);
        }
        return output;

    }
    else {
        return output;
    }
}
template<class t>
bool isIn(vector<t> vec,t item){
    return find(vec.begin(),vec.end(),item)!=vec.end();
}
Path Graph::getMinWay(int begin, int end){
    Path output;
    vector<int> array;
    array.push_back(begin);
    getNode(begin)->visit();
    while(array.size()!=0){
        Node * currentNode = getNode(*(array.begin()));
        array.erase(array.begin());
        for(auto out : currentNode->_out ){
            Node* nextNode = getNode(out);
            if(!nextNode->isVisited()){
                array.push_back(out);
                nextNode->setWave(currentNode->getWave()+1);
                nextNode->visit();
            }
        }
    }
    Node * currentNode = getNode(end);
    while(currentNode!=getNode(begin)){
        int j = 0;
        while(getNode(currentNode->_out[j])->getWave()!=currentNode->getWave()-1){
            j++;
        }
        output._nodePaths.insert(output._nodePaths.begin(),currentNode);
        currentNode = getNode(currentNode->_out[j]);
    }
    output._nodePaths.insert(output._nodePaths.begin(),getNode(begin));
    return output;
}