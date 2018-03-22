
#include <iostream>
#include <vector>
#include "src/treeNode.h"

void changeVector(std::vector<int> &v){
    v[0] = 100;
}

void printVector(std::vector<int> v){
    for (int i=0; i<v.size(); i++){
        std::cout << v[i] << std::endl;
    }
}

int main() {
    int a = 3;
    int *p = &a;
    kdTreeNode<int> node(p);
}