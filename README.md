## Summary

This project implements a simple OCR system that recognizes black digits on a white canvas. It's a university project and is highly unsophisticated -- it works by matching a set of templates on the image. This only works for a single digit with no noise around it, and could be quite mistaken if even the font is different than the used template. It tries to detect digits that are rotated by a maximum of 45 degrees in each direction and digits that are scaled by some kind of factor.

This was mostly just an experiment for me to play with and is probably quite unsuitable for production use (whatever that might mean in this case). It might serve as an interesting code example.

## Compiling and Running

The makefile for compiling the project was adapted from [Learn C The Hard Way](http://c.learncodethehardway.org/book/learn-c-the-hard-waych29.html#x35-18500029.2). To compile the program, use:

    make bin/main

To run it, execute `bin/main` with the filename of the image to be recognized. You can try with some of the templates themselves:

    ./bin/main templates/3.bmp

You could rotate and scale the templates a bit to see how well it does at detecting them. You could also try feeding it digits with a different font or even try drawing some yourself -- in some cases, it manages to recognize even those.

The code in the `tests` directory contains some main functions that exercise the various parts of the program -- scaling, rotation, convolution, and so on.

## How It Works

- The files in the `templates` directory are loaded as `ImageTemplate` objects.

- The given image is loaded as an `Image` object.

- A minimal rotation step is calculated for the image. Starting with 45 degrees
  and halving that on each step, the minimal rotation angle that produces a
  change in the `0, 0` coordinate is found.

- For every rotation of the given image from -45 to 45 degrees, spaced out by
  the calculated step, a match is attempted with the image rotated at that
  angle.

- The rotated image is thresholded to get rid of any gray colors that might
  skew the match and it's trimmed of all background-colored areas on the top,
  left, bottom and right, making the image perfectly fit the actual digit
  inside it.

- The image is scaled down to the template's width and height.

- The convolution of the image and the template image is a single-pixel image.
  The maximum possible intensity of the resulting pixel is calculated by taking
  the auto-convolution of the template image, and the ratio of the result and
  the maximum possible result is taken as a percentage match.

- If the match is better than a predetermined threshold percentage, the tested
  digit is declared a successful match and the program stops. Otherwise, it
  continues with the next digit. The threshold percentage is determined
  experimentally, though admittedly, not a whole lot of experimenting has been
  done.
