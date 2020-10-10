#ifndef PATH_H
#define PATH_H
#include <vector>
using namespace std;

class Node;
class Path{
public:
    vector<Node*> _nodePaths;
    auto getPath(){return _nodePaths;}
    int getLenght(){return _nodePaths.size();}
    void PathAppend(Path input){
        _nodePaths.insert(_nodePaths.end(),input._nodePaths.begin(),input._nodePaths.begin());
    };
};
#endif // !PATH_H