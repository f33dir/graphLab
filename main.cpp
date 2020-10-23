#include <iostream>
#include "Src/Graph.h"
#include "Src/Node.h"
#include "Src/Path.h"
#include <vector>
int main(int, char**) {
    vector<vector<int>> input;//[line][number]
    int size;
    cin >> size;
    input.resize(size);
    for(int i = 0;i< size;i++){
        for(int j = 0;j< size;j++){
            int num;
            cin >>num;
            input[i].push_back(num);
        };
    }

    Graph* graph  = new Graph(input);
    // int a,b;
    // cin >> a;
    // cin >> b;
    // Path way = graph->GetWay(a-1,b-1,true);
    // cout<<way.getLenght()-1<< endl;
    // way = graph->GetWay(a-1,b-1,false);
    // cout<<way.getLenght()-1<< endl;
    auto output =  graph->getCycles();
    cout<<output.size();
}
