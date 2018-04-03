
#include <cmath>
#include <vector>
#include "treeNode.h"
#include "maxHeap.h"

template <class T>
kdTreeNode<T>* searchLeaf(kdTreeNode<T>* root, kdTreeNode<T>* q)
{
    kdTreeNode<T>* leaf=root;
    kdTreeNode<T>* next=nullptr;
    int index=0;
    while(leaf->left != nullptr || leaf->right != nullptr)
    {
        if(q->data[index] < leaf->data[index])
        {
            next = leaf->left;//进入左侧
        }else if(q->data[index] >= leaf->data[index])
        {
            next = leaf->right;
        }
//        else{
//            //当取到中位数时  判断左右子区域哪个更加近
//            if(q->calculateDistance(leaf->left) < q->calculateDistance(leaf->right))
//                next = leaf->left;
//            else
//                next = leaf->right;
//        }

        // 结束了嘛，没结束继续呀
        if(next == nullptr)
            break;//下一个节点是空时  结束了
        else{
            leaf=next;
            if(++index >= root->length)
                index=0;
        }
    }

    return leaf;
}


template <class T>
std::vector<kdTreeNode<T>*> searchKNN(kdTreeNode<T>* root, kdTreeNode<T>* q, int k)
{
    std::vector<kdTreeNode<T>*> knnList;
    kdTreeNode<T>* almostNNode = searchLeaf(root, q);//近似最近点


    while(almostNNode != nullptr)
    {
        float curD = q->calculateDistance(almostNNode);//最近近似点与查询点的距离 也就是球体的半径
        almostNNode->distance = curD;
        maintainMaxKHeap(knnList, almostNNode, k);

        if((almostNNode->parent != nullptr) &&
           (curD > fabs(q->data[almostNNode->parent->partitionDim]
                        - almostNNode->parent->data[almostNNode->parent->partitionDim])))
        {
            //这样可能在另一个子区域中存在更加近似的点
            kdTreeNode<T>* brother = almostNNode->getBrother();
            brother->distance = q->calculateDistance(brother);
            maintainMaxKHeap(knnList, brother, k);
        }

        almostNNode=almostNNode->parent; // 返回上一级
    }

    return knnList;
}