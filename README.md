# cplus
School project for image editing which was demonstrated at the end of the C++ seminar.

Main program is ProjectHertl.cpp

Class Obraz
Responsible for storing the intensity values for individual pixels into the matrix where row and column numbers give positions of those pixels in the image.
Includes methods for image editing such as threshold, black-white image, convolution.
Several operators are overloaded e.g. () cuts the specified part from the image, [] gives access to the pixel intensity on the given coordinates...

Class Kernel
Includes convolution kernels (Identity, Edge Detection, Sharpen, Gaussian Blur, Box Blur...) which are used in convolution method from the class Obraz.

Class Vyjimka
Is used to raise exceptions to chosen invalid operations.

The program uses external library CImg (not included here) for getting pixel intensity values from bmp and for displaying the result of operation to the screen.
