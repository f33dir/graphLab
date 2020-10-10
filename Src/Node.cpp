#include "Node.h"

Node::Node(int id,vector<int> outs){
    this->_id = id;
    for(int i = 0 ;i<outs.size();i++){
        if((i != id)&&(outs[i]== 1)){
            _out.push_back(i);
        }
    }
};

Node::Node(Node*input){
    this->_id = input->_id;
    this->_out = vector<int>(input->_out);
    this->_visited = input->_visited;
    this->_wave = input->_wave;
}