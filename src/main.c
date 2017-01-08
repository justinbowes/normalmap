#include <stdint.h>
#include <stdlib.h>
#include <stb_image.h>
#include <assert.h>
#include <mem.h>
#include <stb_image_write.h>
#include <normalmap.h>
#include <stdbool.h>


const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return "";
    return dot + 1;
}


int main(int argc, const char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <heightmap_filename> <bumpmap_filename>", argv[0]);
        exit(-1);
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];
    int x, y, n;
    uint8_t *image_in = stbi_load(infile, &x, &y, &n, 4);
    if (!image_in) {
        fprintf(stderr, "File %s was not loaded: %s", infile, stbi_failure_reason());
        exit(-2);
    }
    uint8_t *image_out = malloc(x * y * 4);

    // TODO: expose this via command line switches.
    NormalmapVals config = {
            filter: FILTER_NONE,
            wrap: false,
            conversion: CONVERT_RED,
            scale: 2.0f,
            dudv: DUDV_8BIT_UNSIGNED
    };

    int32_t result;
    if ((result = normalmap(image_in, image_out, x, y, config)) != 0) {
        fprintf(stderr, "Failed building normal map, code %d", result);
    }

    const char *ext = get_filename_ext(outfile);
    if (strcmpi("png", ext) == 0) {
        if (!stbi_write_png(outfile, x, y, 4, image_out, 0)) {
            fprintf(stderr, "Unable to write PNG %s", outfile);
        }
    } else if (strcmpi("bmp", ext) == 0) {
        if (!stbi_write_bmp(outfile, x, y, 4, image_out)) {
            fprintf(stderr, "Unable to write BMP %s", outfile);
        }
    } else if (strcmpi("tga", ext) == 0) {
        if (!stbi_write_tga(outfile, x, y, 4, image_out)) {
            fprintf(stderr, "Unable to write TGA %s", outfile);
        }
//    } else if (strcmpi("hdr", ext) == 0) {
//        if (!stbi_write_hdr(outfile, x, y, 4, image_out)) {
//            fprintf(stderr, "Unable to write HDR %s", outfile);
//        }
    } else {
        fprintf(stderr, "Unknown file format for save: %s", ext);
        exit(-1);
    }
    stbi_image_free(image_in);
    free(image_out);
}