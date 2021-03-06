#include "Graph.h"
#include <stack>
#include <set>
#include <algorithm>
#include <math.h>
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
vector<vector<Path>> Graph::getCycles(){
    vector<vector<Path>> output;
    for(int i = 0;i<Nodes.size();i++){
        auto node = getNode(i);
        if(node->getColor() != 1){
            Path temp;
            output.push_back(sortOutReversedPathes(findCycles(temp,node->getId())));
        }
    }
    return output;
}
vector<Path> Graph::findCycles(Path currentPath,int current){
    Node* currentNode = getNode(current);
    currentNode->setColor(1);
    vector<Path> pathes;
    currentPath._nodePaths.push_back(currentNode);
    for(auto next : currentNode->_out){
        Node * nextNode = getNode(next);
        if(nextNode != (currentPath._nodePaths[currentPath._nodePaths.size()-2])){
            if(!isIn(currentPath._nodePaths,nextNode)){
                auto a = findCycles(currentPath,next);
                nextNode->setColor(1);
                pathes.insert(pathes.begin(),a.begin(),a.end());
            }
            else{
                Path nextPath = currentPath;
                nextNode->setColor(1);
                while(nextNode!=nextPath._nodePaths[0])
                    nextPath._nodePaths.erase(nextPath._nodePaths.begin());
                pathes.push_back(nextPath);
            }
        }
    }
    return pathes;
}

vector<Path> Graph::sortOutReversedPathes(vector<Path> input){
    if(input.size()>0){
        int index = 0;
        int size = input.size();
        for(int i = input.size()-1;i>0;i--){
            index++;            
            vector<Node*> tmp = input[max((int)input.size() -index,0)]._nodePaths;
            int j = 0;
            if(input.size()>index){
                while(j<input.size()-index){
                    vector<Node*> tmp2 = input[j]._nodePaths;
                    for(int k = 0;k<tmp.size();k++){
                        Node *  ex = tmp2[0];
                        for(int l = 0;l<tmp2.size()-1;l++){
                            tmp2[l] = tmp2[l+1];
                        };
                        tmp2[tmp2.size()-1] = ex;
                        if(tmp == tmp2){
                            input.erase(input.begin()+j);
                            j--;
                        }
                        std::reverse(tmp2.begin(),tmp2.end());
                        if(tmp == tmp2){
                            input.erase(input.begin()+j);
                            j--;
                        }
                        std::reverse(tmp2.begin(),tmp2.end());
                    }
                    j++;
                }
            }
        }
    }
    return input;
}
