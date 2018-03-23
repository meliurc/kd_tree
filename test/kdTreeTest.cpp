

// test findMedian()
kdTreeTest(){
    int dim = 2;
    int wp[12] = {2, 3, 5, 4, 9, 6, 4, 7, 8, 1, 7, 2};
    int wpLen = sizeof(wp) / sizeof(wp[0]);

    kdTreeNode<int>* node = (kdTreeNode<int>*) malloc(wpLen/dim * sizeof(kdTreeNode<int>));

    for (int i=0; i<(sizeof(wp) / sizeof(wp[0])); i+=dim){
        node[i/dim] = kdTreeNode<int>(wp+i, 2);
    }

    std::cout << "original value of node[1]: " << node[1].data[0] << std::endl;
    kdTreeNode<int>* md = findMedian(node, node+5, 0);
    std::cout << "median is: " << md->data[0] << std::endl;
    std::cout << "after quick sort value of node[1]: " << node[1].data[0] << std::endl;
}
