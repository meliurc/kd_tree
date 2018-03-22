////
// Created by jiguang on 2018/3/19.
//

#ifndef KD_TREE_MAXHEAP_H
#define KD_TREE_MAXHEAP_H

#include "treeNode.h"

template <class T>
void maxHeapFixDown(std::vector<kdTreeNode<T>*> &heapVector, kdTreeNode<T>* newNode);

template <class T>
void maxHeapFixUp(std::vector<kdTreeNode<T>*> &heapVector, kdTreeNode<T>* newNode);

template <class T>
void maintainMaxKHeap(std::vector<kdTreeNode<T>*> heapVector, kdTreeNode<T>* newNode, int k);

#endif //KD_TREE_MAXHEAP_H
