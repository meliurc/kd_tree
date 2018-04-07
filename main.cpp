
#include <iostream>
#include <vector>

#include "src/misc.h"
#include "src/image.h"
#include "src/pnmfile.h"
#include "src/segment-image.h"


int main() {
    char input_image[255] = "panda_input.ppm";
    char output_image[255] = "panda_output.ppm";

    float sigma = 0.5;
    float k = 500;
    int min_size = 20;
    char type[6] = "rgbxy";

    image<rgb> *input = loadPPM(input_image);

    int num_ccs;
    image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs, type);
    savePPM(seg, output_image);
    std::cout << "The photograph has been segmented into: " << num_ccs << " parts.";

}
