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

// define

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
 *
 * @tparam T
 * @param t
 * @param len, number of nodes or number of pixels in an image
 * @param i
 * @param dim
 * @return
 */
template <class T>
kdTreeNode<T>* makeKdTree(kdTreeNode<T> *t, int len, int i, int dim)
{
    kdTreeNode<T> *root;

    if (!len) return nullptr;

    if ((root = findMedian(t, t + len, i))) {
        root->partitionDim = i;
        i = (i + 1) % dim;
        root->left = makeKdTree(t, root - t, i, dim);
        root->right = makeKdTree(root + 1, t + len - (root + 1), i, dim);
    }

    // add pointer to parent
    if(root->left != nullptr)
        root->left->parent = root;
    if(root->right != nullptr)
        root->right->parent = root;
    return root;
}

#endif //KD_TREE_KDTREE_H
