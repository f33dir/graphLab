#ifndef NODE_H
#define NODE_H
#include <vector>
using namespace std;
class Node{
    int _id;
    bool _visited;
    int _wave;
public:
    vector<int> _out;
    Node(int, vector<int>);
    int getId(){return _id;}
    void visit(){_visited = true;};
    bool isVisited(){return _visited;}
    void setWave(int wave){_wave = wave;}
    int getWave(){return _wave;}
};

#endif // !NODE_H
