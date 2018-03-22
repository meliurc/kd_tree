
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
    int a[3] = {1, 2, 3};
    kdTreeNode<int>* nodeA = new kdTreeNode<int>(a, 3);
    int b[3] = {2, 3, 4};
    kdTreeNode<int>* nodeB = new kdTreeNode<int>(b, 3);
    int c[3] = {3, 4, 5};
    kdTreeNode<int>* nodeC = new kdTreeNode<int>(c, 3);
    nodeA->left = nodeB;
    nodeB->parent = nodeA;
    nodeA->right = nodeC;
    nodeC->parent = nodeA;

    // test distance calculation function.
    std::cout << "distinct between B and C is: " << nodeC->calculateDistance(nodeB) << std::endl;

    // test get brother function, check whether the following two address is equal or not.
    std::cout << nodeB << std::endl;
    std::cout << nodeC->getBrother();

}