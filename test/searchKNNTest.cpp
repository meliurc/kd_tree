//
// Created by lrc_h on 2018/3/25.
//

searchKNNTest(){
int dim = 2;
float wp[12] = {2, 3, 5, 4, 9, 6, 4, 7, 8, 1, 7, 2};
int wpLen = sizeof(wp) / sizeof(wp[0]);

kdTreeNode<float>* node = (kdTreeNode<float>*) malloc(wpLen/dim * sizeof(kdTreeNode<float>));

for (int i=0; i<(sizeof(wp) / sizeof(wp[0])); i+=dim){
node[i/dim] = kdTreeNode<float>(wp+i, 2);
}

kdTreeNode<float>* root = makeKdTree(node, wpLen/dim, 0, dim);
printTreeByLevel(root);

float queryPoint[2] = {2, 4.5};
kdTreeNode<float> queryNode = kdTreeNode<float>(queryPoint, 2);
kdTreeNode<float>* queryNodeP = &queryNode;
std::vector<kdTreeNode<float>*> nearestKNode = searchKNN(root, queryNodeP, 3);
for (int i=0; i<nearestKNode.size(); i++)
printNodeData(nearestKNode[i]);
}