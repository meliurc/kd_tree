#ifndef PROJECT_TREENODE_H
#define PROJECT_TREENODE_H

#include <cmath>
#include "treeNode.h"

template <class T>
kdTreeNode<T>::kdTreeNode(T* data) {
    this->data = data;
}

/*!
 * function calculateDistance
 * @tparam T
 * @param node1
 * @param node2
 * @return distance
 */
template <class T>
double kdTreeNode<T>::calculateDistance(kdTreeNode<T>* node1, kdTreeNode<T>* node2){
    double distance = 0;
    for (int i=0; i<node1->length; i++)
        distance += (node1->data[i] - node2->data[i])^2;
    return sqrt(distance);
}

template <class T>
kdTreeNode<T>* kdTreeNode<T>::getBrother(kdTreeNode<T>* node){
    if(node == node->parent->left)
        return node->parent->right;
    else
        return node->parent->left;
}

#endif //PROJECT_TREENODE_H
