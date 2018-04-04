/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#ifndef SEGMENT_IMAGE
#define SEGMENT_IMAGE

#include <cstdlib>
#include <cmath>
#include "image.h"
#include "misc.h"
#include "filter.h"
#include "segment-graph.h"
#include "kdTree/treeNode.h"
#include "kdTree/kdTree.h"
#include "kdTree/searchKNN.h"

// random color
rgb random_rgb(){ 
  rgb c;
  float r;
  
  c.r = (uchar)rand();
  c.g = (uchar)rand();
  c.b = (uchar)rand();

  return c;
}

// dissimilarity measure between pixels
static inline float diff(image<float> *r, image<float> *g, image<float> *b,
			 int x1, int y1, int x2, int y2) {
  return sqrt(square(imRef(r, x1, y1)-imRef(r, x2, y2)) +
	      square(imRef(g, x1, y1)-imRef(g, x2, y2)) +
	      square(imRef(b, x1, y1)-imRef(b, x2, y2)));
}

/*!
 * initialize kd_tree nodes
 * @param smooth_r, smoothed value of color red
 * @param smooth_g, smoothed value of color green
 * @param smooth_b, smoothed value of color blue
 * @param width, width of image in pixels
 * @param height, height of image in pixels
 * @return
 */

kdTreeNode<float>* init_nodes(image<float>* smooth_r, image<float>* smooth_g, image<float>* smooth_b,
                               int width, int height){
    int dim = 5;
    size_t pixel_num = width*height;
    kdTreeNode<float>* node = (kdTreeNode<float>*) malloc(pixel_num * sizeof(kdTreeNode<float>));
    float* data = (float*) malloc(dim*pixel_num*sizeof(float));
    for (int i=0; i<pixel_num; i++){
        int x = i / width;                                      // x, row number start from 0
        int y = i % width;                                      // y, column number start from 0
//        *(data + dim*i)   = x / (float)height;                          // normalize x by height
//        *(data + dim*i+1) = y / (float)width;                         // normalize y by width
//        *(data + dim*i+2) = imRef(smooth_r, y, x) / (float)255;       // normalize r by 255
//        *(data + dim*i+3) = imRef(smooth_g, y, x) / (float)255;       // normalize g by 255
//        *(data + dim*i+4) = imRef(smooth_b, y, x) / (float)255;       // normalize b by 255


        *(data + dim*i) = imRef(smooth_r, y, x);       // normalize r by 255
        *(data + dim*i+1) = imRef(smooth_g, y, x);       // normalize g by 255
        *(data + dim*i+2) = imRef(smooth_b, y, x);       // normalize b by 255
        *(data + dim*i+3) = 0.01*x;                           // normalize x by height
        *(data + dim*i+4) = 0.1*y;                           // normalize y by width
    }
    for (int i=0; i<pixel_num*dim; i+=dim){
        node[i/dim] = kdTreeNode<float>(data+i, dim);
    }

    return node;
}

// generate edges
edge* generate_edges(image<float>* smooth_r, image<float>* smooth_g, image<float>* smooth_b,
                     int width, int height, int &num){
    num = 0;
    edge* edges = new edge[width*height*4];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x < width-1) {
                edges[num].a = y * width + x;
                edges[num].b = y * width + (x+1);
                edges[num].w = diff(smooth_r, smooth_g, smooth_b, x, y, x+1, y);
                num++;
            }

            if (y < height-1) {
                edges[num].a = y * width + x;
                edges[num].b = (y+1) * width + x;
                edges[num].w = diff(smooth_r, smooth_g, smooth_b, x, y, x, y+1);
                num++;
            }

            if ((x < width-1) && (y < height-1)) {
                edges[num].a = y * width + x;
                edges[num].b = (y+1) * width + (x+1);
                edges[num].w = diff(smooth_r, smooth_g, smooth_b, x, y, x+1, y+1);
                num++;
            }

            if ((x < width-1) && (y > 0)) {
                edges[num].a = y * width + x;
                edges[num].b = (y-1) * width + (x+1);
                edges[num].w = diff(smooth_r, smooth_g, smooth_b, x, y, x+1, y-1);
                num++;
            }
        }
    }
    return edges;
}


/*
 * Segment an image
 *
 * Returns a color image representing the segmentation.
 *
 * im: image to segment.
 * sigma: to smooth the image.
 * c: constant for treshold function.
 * min_size: minimum component size (enforced by post-processing stage).
 * num_ccs: number of connected components in the segmentation.
 */
image<rgb> *segment_image(image<rgb> *im, float sigma, float c, int min_size,
			  int *num_ccs, const char* type) {
//    edge* edges;
    int edge_num = 0;
    int width = im->width();
    int height = im->height();
    size_t pixel_num = width*height;

    image<float> *r = new image<float>(width, height);
    image<float> *g = new image<float>(width, height);
    image<float> *b = new image<float>(width, height);

    // smooth each color channel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            imRef(r, x, y) = imRef(im, x, y).r;
            imRef(g, x, y) = imRef(im, x, y).g;
            imRef(b, x, y) = imRef(im, x, y).b;
        }
    }

    image<float> *smooth_r = smooth(r, sigma);
    image<float> *smooth_g = smooth(g, sigma);
    image<float> *smooth_b = smooth(b, sigma);
    delete r; delete g; delete b;

//    std::cout << imRef(smooth_r, 0, 487);

//    // initialize kd_tree node when T is struct xyrgb
//    if (strcmp(type, "xyrgb") == 0) {
//        int K = 10;
//        int dim = 5;
//        kdTreeNode<float> *node = init_nodes(smooth_r, smooth_g, smooth_b, width, height);
//        kdTreeNode<float> *root = makeKdTree(node, pixel_num, 0, dim);
//
//        // generate edges
//        edges = new edge[K*pixel_num];
//        kdTreeNode<float> *queryNodeP = node;
//        std::vector<kdTreeNode<float>*> nearestKNode = searchKNN(root, queryNodeP, K);
//        for (int j=0; j<nearestKNode.size(); j++){
//            (edges + 0*K + j)->a = (int)round(queryNodeP->data[0]*height*width + queryNodeP->data[1]*height);
//            (edges + 0*K + j)->b = (int)round(nearestKNode[j]->data[0]*height*width + nearestKNode[j]->data[1]*height);
//            (edges + 0*K + j)->w = nearestKNode[j]->distance;

//        for (int i=0; i<pixel_num; i++){
//            kdTreeNode<float> *queryNodeP = node + i;
//            std::vector<kdTreeNode<float>*> nearestKNode = searchKNN(root, queryNodeP, K);
//            for (int j=0; j<nearestKNode.size(); j++){
//                (edges + i*K + j)->a = (int)round(queryNodeP->data[0]*height*width + queryNodeP->data[1]*height);
//                (edges + i*K + j)->b = (int)round(nearestKNode[j]->data[0]*height*width + nearestKNode[j]->data[1]*height);
//                (edges + i*K + j)->w = nearestKNode[j]->distance;
//                edge_num++;
//            }
//        }
//    }
    // or generate edges directly
//    else{
//        edges = generate_edges(smooth_r, smooth_g, smooth_b, width, height, edge_num);
//    }

//    image<float> *smooth_r = r;
//    image<float> *smooth_g = g;
//    image<float> *smooth_b = b;
//    delete r; delete g; delete b;

////    std::cout << imRef(smooth_r, 0, 487);
//
//    // initialize kd_tree node when T is struct xyrgb
//    if (strcmp(type, "xyrgb") == 0) {
//        int K = 10;
//        int dim = 5;
//        kdTreeNode<float> *node = init_nodes(smooth_r, smooth_g, smooth_b, width, height);
//        kdTreeNode<float> *root = makeKdTree(node, pixel_num, 0, dim);
//
//        // generate edges
//        edges = new edge[K*pixel_num];
//        kdTreeNode<float> *queryNodeP = node;
//        std::vector<kdTreeNode<float>*> nearestKNode = searchKNN(root, queryNodeP, K);
//        for (int j=0; j<nearestKNode.size(); j++){
//            (edges + 0*K + j)->a = (int)round(queryNodeP->data[0]*height*width + queryNodeP->data[1]*height);
//            (edges + 0*K + j)->b = (int)round(nearestKNode[j]->data[0]*height*width + nearestKNode[j]->data[1]*height);
//            (edges + 0*K + j)->w = nearestKNode[j]->distance;
//
////        for (int i=0; i<pixel_num; i++){
////            kdTreeNode<float> *queryNodeP = node + i;
////            std::vector<kdTreeNode<float>*> nearestKNode = searchKNN(root, queryNodeP, K);
////            for (int j=0; j<nearestKNode.size(); j++){
////                (edges + i*K + j)->a = (int)round(queryNodeP->data[0]*height*width + queryNodeP->data[1]*height);
////                (edges + i*K + j)->b = (int)round(nearestKNode[j]->data[0]*height*width + nearestKNode[j]->data[1]*height);
////                (edges + i*K + j)->w = nearestKNode[j]->distance;
////                edge_num++;
////            }
//        }
//    }
//    // or generate edges directly
//    else{
//        edges = generate_edges(smooth_r, smooth_g, smooth_b, width, height, edge_num);
//    }

    int K = 10;
    int dim = 5;
    kdTreeNode<float> *node = init_nodes(smooth_r, smooth_g, smooth_b, width, height);
    kdTreeNode<float> *root = makeKdTree(node, pixel_num, 0, dim);

    edge* edges = new edge[K*pixel_num];
    for (int i=0; i<pixel_num; i++) {
        kdTreeNode<float> *queryNodeP = node + i;
        std::vector<kdTreeNode<float> *> nearestKNode = searchKNN(root, queryNodeP, K);
        for (int j = 0; j < nearestKNode.size(); j++) {
//            (edges + i * K + j)->a = (int) round(queryNodeP->data[0] * height * width + queryNodeP->data[1] * height);
//            (edges + i * K + j)->b = (int) round(nearestKNode[j]->data[0] * height * width + nearestKNode[j]->data[1] * height);
//            (edges + i * K + j)->w = nearestKNode[j]->distance;
//            edge_num++;

            (edges + i * K + j)->a = (int) round(queryNodeP->data[3] * 100 * width + queryNodeP->data[4] * 10);
            (edges + i * K + j)->b = (int) round(nearestKNode[j]->data[3] * 100 * width + nearestKNode[j]->data[4] * 10);
            (edges + i * K + j)->w = nearestKNode[j]->distance;
            edge_num++;
        }
    }


    delete smooth_r;
    delete smooth_g;
    delete smooth_b;

    // segment
    universe *u = segment_graph(pixel_num, edge_num, edges, c);

    // post process small components
    for (int i = 0; i < edge_num; i++) {
        int a = u->find(edges[i].a);
        int b = u->find(edges[i].b);
        if ((a != b) && ((u->size(a) < min_size) || (u->size(b) < min_size)))
            u->join(a, b);
    }
    delete [] edges;
    *num_ccs = u->num_sets();

    image<rgb> *output = new image<rgb>(width, height);

    // pick random colors for each component
    rgb *colors = new rgb[width*height];
    for (int i = 0; i < width*height; i++)
        colors[i] = random_rgb();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int comp = u->find(y * width + x);
            imRef(output, x, y) = colors[comp];
        }
    }

    delete [] colors;
    delete u;

    return output;
}


#endif
