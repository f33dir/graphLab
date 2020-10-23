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
            Path passed;
            passed._nodePaths.push_back(getNode(begin));
            output = getMaxWay(begin,end,Nodes,passed);
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
        Node * nextNode = getNode(0);
        while(!((nextNode->getWave()==(currentNode->getWave()-1))&&(isIn(nextNode->_out,currentNode->getId())))){
            j++;
            nextNode = getNode(j);
        }
        currentNode = nextNode;
        output._nodePaths.insert(output._nodePaths.begin(),currentNode);
    }
    output._nodePaths.insert(output._nodePaths.begin(),getNode(begin));
    return output;
}
Path Graph::getMaxWay(int begin,int end,vector<Node*> tree,Path passed){
    if(begin == end){
        return passed;
    };
    Path output;
    vector<Node*> newTree;
    for(auto item:tree){
        newTree.push_back(new Node(item));
    }
    newTree[begin]->visit();
    vector<Path> Pathes;
    for(auto node : newTree[begin]->_out){
        Node  * current = getNode(node,newTree);
        if(!current->isVisited()){
            Path newPath = passed;
            newPath._nodePaths.push_back(current);
            Pathes.push_back(getMaxWay(node,end,newTree,newPath));
        }
    }
    int maxLenght;
    for(auto path :Pathes){
        if(path.getLenght()>maxLenght){
            maxLenght = path.getLenght();
            output = path;
        }
    }
    return output;
}