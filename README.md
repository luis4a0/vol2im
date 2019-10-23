# Vol2im

This program embeds volumetric data in various image files, using their RGBA or RGB channels. Each slice of the original model is represented as one channel of the output file.

The output images can be used as 3D textures to perform volumetric visualization in GLSL.

Vol2im currently accepts only inputs and output in PNG format.

Images can be converted using, for instance, Graphics Magick (in Unix):
        `convert input.tif output.png`
(In the folder scripts/ there are some scripts which may help in converting
multiple files at once.)

## Use

To generate an image containing four slices:
        `./vol2im -4i a.png b.png c.png d.png -o output.png`

To generate an image containing 16 slices:
        `./vol2im -16i 1.png 2.png 3.png 4.png 5.png 6.png 7.png 8.png 9.png 10.png 11.png 12.png 13.png 14.png 15.png 16.png -o output.png`
