
#include <iostream>
#include <vector>
#include "src/kdTree/treeNode.h"
#include "src/kdTree/kdTree.h"
#include "src/kdTree/searchKNN.h"
#include "src/kdTree/utils.h"


int main() {
    int dim = 2;
    double wp[12] = {2, 3, 5, 4, 9, 6, 4, 7, 8, 1, 7, 2};
    int wpLen = sizeof(wp) / sizeof(wp[0]);

    kdTreeNode<double>* node = (kdTreeNode<double>*) malloc(wpLen/dim * sizeof(kdTreeNode<double>));

    for (int i=0; i<(sizeof(wp) / sizeof(wp[0])); i+=dim){
        node[i/dim] = kdTreeNode<double>(wp+i, 2);
    }

    kdTreeNode<double>* root = makeKdTree(node, wpLen/dim, 0, dim);
    printTreeByLevel(root);

    double queryPoint[2] = {2, 4.5};
    kdTreeNode<double> queryNode = kdTreeNode<double>(queryPoint, 2);
    kdTreeNode<double>* queryNodeP = &queryNode;
    std::vector<kdTreeNode<double>*> nearestKNode = searchKNN(root, queryNodeP, 3);
    for (int i=0; i<nearestKNode.size(); i++)
        printNodeData(nearestKNode[i]);
}
