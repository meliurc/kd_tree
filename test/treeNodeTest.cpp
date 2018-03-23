//
// Created by jiguang on 2018/3/22.
//

test_treeNode(){
    int a[3] = {1, 2, 3};
    kdTreeNode<int>* nodeA = new kdTreeNode<int>(a, 3);
    int b[3] = {2, 3, 4};
    kdTreeNode<int>* nodeB = new kdTreeNode<int>(b, 3);
    int c[3] = {3, 4, 5};
    kdTreeNode<int>* nodeC = new kdTreeNode<int>(c, 3);
    nodeA->left = nodeB;
    nodeB->parent = nodeA;
    nodeA->right = nodeC;
    nodeC->parent = nodeA;

    // test distance calculation function.
    std::cout << "distinct between B and C is: " << nodeC->calculateDistance(nodeB) << std::endl;

    // test get brother function, check whether the following two address is equal or not.
    std::cout << nodeB << std::endl;
    std::cout << nodeC->getBrother();

    // new with malloc
    int dim = 2;
    int wp[12] = {2, 3, 5, 4, 9, 6, 4, 7, 8, 1, 7, 2};
    int wpLen = sizeof(wp) / sizeof(wp[0]);

    kdTreeNode<int>* node = (kdTreeNode<int>*) malloc(wpLen/dim * sizeof(kdTreeNode<int>));

    for (int i=0; i<(sizeof(wp) / sizeof(wp[0])); i+=dim){
        node[i/dim] = kdTreeNode<int>(wp+i, 2);
    }
    std::cout << node->data[0] << std::endl;
    std::cout << node->data[1] << std::endl;
    std::cout << (node+1)->data[0] << std::endl;
    std::cout << (node+1)->data[1] << std::endl;
}