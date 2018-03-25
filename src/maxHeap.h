////
// Created by jiguang on 2018/3/19.
//

#ifndef KD_TREE_MAXHEAP_H
#define KD_TREE_MAXHEAP_H

#include <vector>
#include "treeNode.h"

template <class T>
void maxHeapFixDown(std::vector<kdTreeNode<T>*> &heapVector, kdTreeNode<T>* newNode);

template <class T>
void maxHeapFixUp(std::vector<kdTreeNode<T>*> &heapVector, kdTreeNode<T>* newNode);

template <class T>
void maintainMaxKHeap(std::vector<kdTreeNode<T>*> &heapVector, kdTreeNode<T>* newNode, int k);


/*!
 *
 * @tparam T
 * @param heapVector
 * @param newNode
 */
template <class T>
void maxHeapFixDown(std::vector<kdTreeNode<T>*> &heapVector, kdTreeNode<T>* newNode)
{
    heapVector[0] = newNode;
    int i = 0;
    int j = 2*i+1;
    while(j<heapVector.size())
    {
        if(j+1<heapVector.size() && heapVector[j]->distance < heapVector[j+1]->distance)
            j++;

        if(heapVector[i]->distance >= heapVector[j]->distance)
            break;

        kdTreeNode<T>* t = heapVector[i];
        heapVector[i] = heapVector[j];
        heapVector[j] = t;

        i = j;
        j = i*2+1;
    }
}

/*!
 *
 * @tparam T
 * @param heapVector
 * @param newNode
 */
template <class T>
void maxHeapFixUp(std::vector<kdTreeNode<T>*> &heapVector, kdTreeNode<T>* newNode)
{
    heapVector.push_back(newNode);
    int j=heapVector.size()-1;
    int i=(j+1)/2-1;//i是parent节点
    while(i>=0)
    {

        if(heapVector[i]->distance >= heapVector[j]->distance)
            break;

        kdTreeNode<T>* t = heapVector[i];
        heapVector[i] = heapVector[j];
        heapVector[j] = t;

        j = i;
        i = (j+1)/2-1;
    }
}

/*!
 *
 * @tparam T
 * @param heapVector
 * @param newNode
 * @param k
 */
template <class T>
void maintainMaxKHeap(std::vector<kdTreeNode<T>*> &heapVector, kdTreeNode<T>* newNode, int k)
{
    if(heapVector.size()<k)
    {
        maxHeapFixUp(heapVector, newNode);//不足k个堆   直接向上修复
    }else if(newNode->distance < heapVector[0]->distance){
        //比堆顶的要小   还需要向下修复 覆盖堆顶
        maxHeapFixDown(heapVector, newNode);
    }
}

#endif //KD_TREE_MAXHEAP_H
