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
    int partitionDim;        // on which dimension this node partition the space
    float distance;
    kdTreeNode<T>* left;
    kdTreeNode<T>* right;
    kdTreeNode<T>* parent;

    kdTreeNode();
    kdTreeNode(T* data, int length);
    ~kdTreeNode();
    float calculateDistance(kdTreeNode<T>* anotherNode);
    kdTreeNode<T>* getBrother();
};

template <class T>
kdTreeNode<T>::kdTreeNode(){
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

template <class T>
kdTreeNode<T>::kdTreeNode(T* data, int length) {
    this->data = data;
    this->length = length;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

template <class T>
kdTreeNode<T>::~kdTreeNode(){}

/*!
 * calculate Euclidian distance between two nodes
 * @tparam T
 * @param node1
 * @param node2
 * @return distance
 */
template <class T>
float kdTreeNode<T>::calculateDistance(kdTreeNode<T>* anotherNode){
    float distance = 0;
    for (int i=0; i<this->length; i++) {
        distance += pow((this->data[i] - anotherNode->data[i]), 2);
    }
    return sqrt(distance);
}

/*!
 * get brother node of current node
 * @tparam T
 * @return
 */
template <class T>
kdTreeNode<T>* kdTreeNode<T>::getBrother(){
    if(this == this->parent->left)
        return this->parent->right;
    else
        return this->parent->left;
}

#endif //KD_TREE_TREENODE_H
