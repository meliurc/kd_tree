//
// Created by jiguang on 2018/3/19.
//

#ifndef KD_TREE_TREENODE_H
#define KD_TREE_TREENODE_H

template <class T>
class kdTreeNode{
public:
    T* data;
    int length;
    double distance;
    kdTreeNode<T>* left;
    kdTreeNode<T>* right;
    kdTreeNode<T>* parent;

    kdTreeNode(T* data);
    ~kdTreeNode();
    double calculateDistance(kdTreeNode* node1, kdTreeNode* node2);
    kdTreeNode* getBrother(kdTreeNode* Node);
};



#endif //KD_TREE_TREENODE_H
