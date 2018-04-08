//
// Created by jiguang on 2018/3/21.
//

#ifndef KD_TREE_KDTREE_H
#define KD_TREE_KDTREE_H

#include <vector>
#include <cstring>
#include "treeNode.h"

// declare

template <class T>
void swap(kdTreeNode<T> *x, kdTreeNode<T> *y);

template <class T>
kdTreeNode<T>* findMedian(kdTreeNode<T> *start, kdTreeNode<T> *end, int index);

template <class T>
kdTreeNode<T>* makeKdTree(kdTreeNode<T> *t, int len, int i, int dim);


template <class T>
float calculateMean(kdTreeNode<T> *t, int len, int i, int dim){
    float sum = 0;
    for (int k=0; k<len; k++){
        sum += t->data[k*dim + i];
    }
    return sum/len;
}


template <class T>
float calculateVariance(kdTreeNode<T> *t, int len, int i, int dim){
    float sum = 0;
    float mean = calculateMean(t, len, i, dim);
    for (int k=0; k<len; k++){
        sum += (t->data[k*dim + i] - mean) * (t->data[k*dim + i] - mean);
    }
    return sum/len;
}


template <class T>
int choosePartitionDim(kdTreeNode<T> *t, int len, int dim){
    float maxVar = 0;
    int maxIndex = 0;
    for (int k=0; k<dim; k++){
        float variance = calculateVariance(t, len, k, dim);
        if (variance > maxVar){
            maxVar = variance;
            maxIndex = k;
        }
    }

    return maxIndex;
}

/*!
 * swap data between two kdTreeNode
 * @tparam T
 * @param x
 * @param y
 */
template <class T>
void swap(kdTreeNode<T> *x, kdTreeNode<T> *y) {
    int len = x->length;
    T tmp[len];
    memcpy(tmp, x->data, len*sizeof(T));
    memcpy(x->data, y->data, len*sizeof(T));
    memcpy(y->data, tmp, len*sizeof(T));
}

/*!
 * find median by quick sort
 * @tparam T
 * @param start
 * @param end
 * @param index
 * @return
 */
template <class T>
kdTreeNode<T>* findMedian(kdTreeNode<T> *start, kdTreeNode<T> *end, int index)
{
    if (end <= start) return nullptr;
    if (end == start + 1)
        return start;

    kdTreeNode<T> *p, *store, *md = start + (end - start) / 2;
    kdTreeNode<T> *pivot;
    while (1) {
        pivot = start;

        store = pivot + 1;
        for (p = pivot+1; p < end; p++) {
            if (p->data[index] < pivot->data[index]) {
                if (p != store)
                    swap(p, store);
                store++;
            }
        }
        swap(pivot, store - 1);

        /* when store == median, store is median */
        if ((store - 1)->data[index] == md->data[index])
            return md;

        if (store > md)
            end = store;
        else
            start = store;
    }
}

/*!
 * build KD tree
 * @tparam T
 * @param t: pointer to the first node of node list.
 * @param len: number of nodes or number of pixels in an image.
 * @param i: partitioned by ith dimension.
 * @param dim: length of node->data.
 * @return
 */
template <class T>
kdTreeNode<T>* makeKdTree(kdTreeNode<T> *t, int len, int i, int dim, const char* type)
{
    kdTreeNode<T> *root;

    if (!len)
        return nullptr;
    else if (len == 1)
        return t;

    if (strcmp(type, "max_variance") == 0)
        i = choosePartitionDim(t, len, dim);

    if ((root = findMedian(t, t + len, i))) {
        root->partitionDim = i;
        i = (i + 1) % dim;
        root->left = makeKdTree(t, root - t, i, dim, type);
        root->right = makeKdTree(root + 1, t + len - (root + 1), i, dim, type);
    }

    // add pointer to parent
    if(root->left != nullptr)
        root->left->parent = root;
    if(root->right != nullptr)
        root->right->parent = root;
    return root;
}

#endif //KD_TREE_KDTREE_H
