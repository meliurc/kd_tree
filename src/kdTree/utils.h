
#include<queue>
#include "treeNode.h"

/*!
 * print node->data
 * @tparam T
 * @param root
 */
template <class T>
void printNodeData(kdTreeNode<T>* root){
    std::cout << "data in node: (";
    for (int i=0; i<root->length; i++)
        if (i < root->length - 1)
            std::cout << root->data[i] << ", ";
        else
            std::cout << root->data[i] << ")" << std::endl;
}

/*!
 * print tree by level
 * @tparam T
 * @param root
 */
template <class T>
void printTreeByLevel(kdTreeNode<T>* root)
{
    std::queue<kdTreeNode<T>*> que;
    kdTreeNode<T> *tmp;
    if(root)
    {
        que.push(root);
        while(!que.empty())
        {
            tmp=que.front();
            que.pop();

            std::cout << "partition dimension: " << tmp->partitionDim << ", ";
            printNodeData(tmp);

            // insert left and right node into queue if not null
            if(tmp->left)
                que.push(tmp->left);
            if(tmp->right)
                que.push(tmp->right);
        }
    }
}