
#include <iostream>
#include <vector>
#include "src/treeNode.h"
#include "src/kdTree.h"
#include "src/utils.h"


void changeVector(std::vector<int> &v){
    v[0] = 100;
}

void printVector(std::vector<int> v){
    for (int i=0; i<v.size(); i++){
        std::cout << v[i] << std::endl;
    }
}

int main() {
    int dim = 2;
    int wp[12] = {2, 3, 5, 4, 9, 6, 4, 7, 8, 1, 7, 2};
    int wpLen = sizeof(wp) / sizeof(wp[0]);

    kdTreeNode<int>* node = (kdTreeNode<int>*) malloc(wpLen/dim * sizeof(kdTreeNode<int>));

    for (int i=0; i<(sizeof(wp) / sizeof(wp[0])); i+=dim){
        node[i/dim] = kdTreeNode<int>(wp+i, 2);
    }

    kdTreeNode<int>* root = makeKdTree(node, wpLen/dim, 0, dim);
    printTreeByLevel(root);



}
