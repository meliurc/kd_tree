
#include<queue>
#include "treeNode.h"

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

            std::cout << "(";
            for (int i=0; i<tmp->length; i++)
                if (i<tmp->length-1)
                    std::cout << tmp->data[i] << ", ";
                else
                    std::cout << tmp->data[i] << ")" << std::endl;

            if(tmp->left)  //左子树非空时入队
                que.push(tmp->left);
            if(tmp->right) //右子树非空时入队
                que.push(tmp->right);
        }
    }
}