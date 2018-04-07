
#include <cmath>
#include <vector>
#include "treeNode.h"
#include "maxHeap.h"

/*!
 * find the deepest leaf node that is within the same region as the query node.
 * @tparam T
 * @param root: root of KD tree.
 * @param q: query node.
 * @return leaf: the leaf node that is in the same region as the query node.
 */
template <class T>
kdTreeNode<T>* searchLeaf(kdTreeNode<T>* root, kdTreeNode<T>* q)
{
    kdTreeNode<T>* leaf=root;
    kdTreeNode<T>* next=nullptr;
    int index=0;
    while(leaf->left != nullptr || leaf->right != nullptr)
    {
        // choose one side to continue searching
        if(q->data[index] < leaf->data[index])
        {
            next = leaf->left;
        }else if(q->data[index] > leaf->data[index])
        {
            next = leaf->right;
        }
        // when query node's data is equal to the median value, which side should we search.
        else{
            // if leaf node has both leaf and right node, enter the nearer side
            if ((leaf->left != nullptr) && (leaf->right != nullptr)){
                if(q->calculateDistance(leaf->left) < q->calculateDistance(leaf->right))
                    next = leaf->left;
                else
                    next = leaf->right;
            // if leaf node has only one non-null child node, enter the non-null child node
            } else if (leaf->left == nullptr)
                next = leaf->right;
            else
                next = leaf->left;
        }

        // when the next points to a nullptr, then end searching and return leaf.
        if(next == nullptr)
            break;
        else{
            leaf=next;
            if(++index >= root->length)
                index=0;
        }
    }

    return leaf;
}

/*!
 * search for k nearest node to query node.
 * @tparam T
 * @param root: root of KD tree.
 * @param q: query node.
 * @param k: number of nearest node to search for.
 * @return
 */
template <class T>
std::vector<kdTreeNode<T>*> searchKNN(kdTreeNode<T>* root, kdTreeNode<T>* q, int k)
{
    std::vector<kdTreeNode<T>*> knnList;
    kdTreeNode<T>* almostNode = searchLeaf(root, q);    // the deepest node within the same region as q


    while(almostNode != nullptr)
    {
        float curD = q->calculateDistance(almostNode);  // distance to "almost node"
        almostNode->distance = curD;
        maintainMaxKHeap(knnList, almostNode, k);

        // is there might exists a nearer node in the neighbor region of current region
        if((almostNode->parent != nullptr) &&
           (curD > fabs(q->data[almostNode->parent->partitionDim]
                        - almostNode->parent->data[almostNode->parent->partitionDim])))
        {
            // get current region's neighbor(or called brother)
            kdTreeNode<T>* brother = almostNode->getBrother();
            if (brother != nullptr) {
                brother->distance = q->calculateDistance(brother);
                maintainMaxKHeap(knnList, brother, k);
            }
        }

        almostNode=almostNode->parent;                  // enter the parent node
    }

    return knnList;
}