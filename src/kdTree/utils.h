
#include<queue>
#include "treeNode.h"

template <class T>
void printNodeData(kdTreeNode<T>* root){
    std::cout << "data in node: (";
    for (int i=0; i<root->length; i++)
        if (i < root->length - 1)
            std::cout << root->data[i] << ", ";
        else
            std::cout << root->data[i] << ")" << std::endl;
}

template <class T>
void printTreeByLevel(kdTreeNode<T>* root)
{
    std::queue<kdTreeNode<T>*> que;
    kdTreeNode<T> *tmp; //保存队列岀队时的临时变量
    if(root) //当头节点不为空时
    {
        que.push(root);
        while(!que.empty())
        {
            tmp=que.front(); //取队首元素
            que.pop();  //岀队

            std::cout << "partition dimension: " << tmp->partitionDim << ", ";
            printNodeData(tmp);

            if(tmp->left)  //左子树非空时入队
                que.push(tmp->left);
            if(tmp->right) //右子树非空时入队
                que.push(tmp->right);
        }
    }
}