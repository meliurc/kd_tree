
#include <iostream>
#include <vector>

#include "src/misc.h"
#include "src/image.h"
#include "src/pnmfile.h"
#include "src/segment-image.h"


int main() {
    float sigma = 0.5;
    float k = 500;
    int min_size = 20;
    int num_ccs = 0;
    char type[100] = "xyrgb";

    image<rgb> *input = loadPPM("panda.ppm");
    image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs, type);

}
