//
// Created by jiguang on 2018/3/19.
//

#ifndef KD_TREE_TREENODE_H
#define KD_TREE_TREENODE_H

#include <iostream>
#include <cmath>


template <class T>
class kdTreeNode{
public:
    T* data;
    int length;
    double distance;
    kdTreeNode<T>* left;
    kdTreeNode<T>* right;
    kdTreeNode<T>* parent;

    kdTreeNode();
    kdTreeNode(T* data, int length);
    ~kdTreeNode();
    double calculateDistance(kdTreeNode<T>* anotherNode);
    kdTreeNode<T>* getBrother();
};

template <class T>
kdTreeNode<T>::kdTreeNode(){}

template <class T>
kdTreeNode<T>::kdTreeNode(T* data, int length) {
    this->data = data;
    this->length = length;
}

template <class T>
kdTreeNode<T>::~kdTreeNode(){}

/*!
 * function calculateDistance
 * @tparam T
 * @param node1
 * @param node2
 * @return distance
 */
template <class T>
double kdTreeNode<T>::calculateDistance(kdTreeNode<T>* anotherNode){
    double distance = 0;
    for (int i=0; i<this->length; i++) {
        distance += pow((this->data[i] - anotherNode->data[i]), 2);
    }
    return sqrt(distance);
}

template <class T>
kdTreeNode<T>* kdTreeNode<T>::getBrother(){
    if(this == this->parent->left)
        return this->parent->right;
    else
        return this->parent->left;
}

#endif //KD_TREE_TREENODE_H
