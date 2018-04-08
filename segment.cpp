
#include <cstdio>
#include <cstdlib>

#include "src/misc.h"
#include "src/image.h"
#include "src/pnmfile.h"
#include "src/segment-image.h"


int main(int argc, char **argv) {
    if (argc != 9){
        fprintf(stderr, "usage: %s sigma k min_size type xZoom yZoom input(ppm) output(ppm)\n", argv[0]);
        return 1;
    }

    float sigma = atof(argv[1]);
    float k = atof(argv[2]);
    int min_size = atoi(argv[3]);
    char* segType = argv[4];

    int xZoom = atoi(argv[5]);
    int yZoom = atoi(argv[6]);

    char* input_image = argv[7];
    char* output_image = argv[8];

//    float sigma = 0.5;
//    float k = 500;
//    int min_size = 20;
//    char segType[6] = "rgbxy";
//    int xZoom = 100;
//    int yZoom = 5;

    // default method to build KD tree: r-g-b-x-y, or change kdTreeType="max_variance" to partition by max variance.
    char kdTreeType[20] = "in_turn";

    image<rgb> *input = loadPPM(input_image);

    int num_ccs = 0;
    image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs, xZoom, yZoom, segType, kdTreeType);
    savePPM(seg, output_image);
    std::cout << "The photograph has been segmented into: " << num_ccs << " parts.";

}
