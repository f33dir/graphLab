#ifndef PATH_H
#define PATH_H
#include <vector>
using namespace std;

class Node;
class Path{
public:
    vector<Node*> _nodePaths;
    auto getPath(){return _nodePaths;}
};
#endif // !PATH_H