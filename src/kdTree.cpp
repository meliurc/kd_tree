//
// Created by jiguang on 2018/3/21.
//

#include <vector>
#include <cstring>
#include "treeNode.h"
#include "kdTree.h"

/*!
 * swap data between two kdTreeNode
 * @tparam T
 * @param x
 * @param y
 */
template <class T>
void swap(kdTreeNode<T> *x, kdTreeNode<T> *y) {
    int len = sizeof(x->data) / sizeof(x->data[0]);
    T tmp[len];
    memcpy(tmp, x->data, sizeof(tmp));
    memcpy(x->data, y->data, sizeof(tmp));
    memcpy(y->data, tmp, sizeof(tmp));
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
    double pivot;
    while (1) {
        pivot = start->data[index];

        for (store = p = start; p < end; p++) {
            if (p->data[index] < pivot) {
                if (p != store)
                    swap(p, store);
                store++;
            }
        }
        swap(store, start);

        /* when store == median, store is median */
        if (store->data[index] == md->data[index])
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
 * @param len
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
        i = (i + 1) % dim;
        root->left  = makeKdTree(t, root - t, i, dim);
        root->right = makeKdTree(root + 1, t + len - (root + 1), i, dim);
    }
    return root;
}
