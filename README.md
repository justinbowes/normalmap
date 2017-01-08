# normalmap
Command line utility to convert height maps to DU-DV normal maps.

## Platforms

[Windows binary](https://github.com/justinbowes/normalmap/releases) is provided.

Should compile and run on any modern GCC or Clang compiler. CMake build script is provided.

## Usage

`normalmap.exe infile outfile`

The height will be taken from the red channel of the source image. RGBA PNGs are tested and recommended but any image type supported by stb_image should work.

The output will be an unfiltered, 8-bit unsigned du/dv map, which can be used as a normal map in rendering applications. The heightmap sampler is a 2x2 box.

The underlying normal map generation code is inherited from The GIMP and is considerably more flexible. In this version, you must update `main.c` and rebuild to change the following settings:

* Scale *default = 2.0*
* Sampler filter
  * None *default*
  * Sobel 3x3, 5x5
  * Prewitt 3x3, 5x5,
  * Generic 3x3, 5x5, 7x7, 9x9
* Height source:
  * Luminance
  * Unbias RGB
  * Red *default*, Green or Blue channel
  * Alpha channel: height, height inverted
* Output type:
  * du/dv 8-bit signed *default*, 8-bit unsigned, 16-bit signed, 16-bit unsigned
  * true "normalized" normal

Note that the effect of du/dv output being unnormalized is that normal vectors constructed by sampling the map will require normalization in your shader or image loader, which means in turn that the effect of the scale parameter above is less pronounced than it would be otherwise.
