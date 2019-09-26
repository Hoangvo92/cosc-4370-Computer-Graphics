/*******************************************************
 * Homework 1: Rasterization                           *
 * CS 148 (Summer 2016), Stanford University           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method you derived in the written portion of the    *
 * homework.                                           *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int size;
bool **image;

void renderPixel(int x, int y) {
    /*input: integer values x and y which are location of the
       pixel (x,y) on the image
      output: nothing
      function: light up the pixel (x,y) and its symmetric
      counterpart (y,x)
    */
	assert(x >= 0 && y >= 0 && x <= size && y <= size);
	image[x][y] = 1;

	// TODO:  light up the pixel's symmetric counterpart

    //  The arch is 1/4 circle, at the first section, so
    //symmetric counter part is the reflected image between
    // the line of 45 degree, counter part of (x,y) is (y,x)
    image[y][x] = 1;

}

void rasterizeArc(int radius) {
    /*Input: the integer value radius, the radius r of a circle
     output: nothing
     function: using the radius and renderPixel to draw an arc of 1/4 circle
     applying the midpoint circle algorithm
     */
	// TODO:  rasterize the arc using renderPixel to light up pixels
    int x = 0;
    int y = radius;
    //d=(x + 1)^2 + (y-1/2)^2 -radius^2
    //at the beginning x=0, y=radius =>
    double d= 5.0 / 4.0 - radius;
    renderPixel(x, y);

    //Begin drawing pixel
    while (y > x) {
    //if d_old <0 ->next midpoint will be one increment over in x
      if (d < 0) {
          //d_new = F(x+1 +1, y-1/2), the point outside circle
         d += 2.0 * x + 3.0;
      }
      else {
          //if d_old>0-> the next midpoint will be one increment over in x
          // and one increment down in y
          //d_new =F(x+1,y-1/2-1), the point inside circle
         d += 2.0 * (x- y) + 5.0;
         y--;
      }
      x++;
      renderPixel(x, y); //at the new pixel, we light up
     }
}

// You shouldn't need to change anything below this point.

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " circleSize\n";
		return 0;
	}

#ifdef _WIN32
	sscanf_s(argv[1], "%d", &size);
#else
	sscanf(argv[1], "%d", &size);
#endif
	if (size <= 0) {
		cout << "Image must be of positive size.\n";
		return 0;
	}

	// reserve image as 2d array
	image = new bool*[size+1];
	for (int i = 0; i <= size; i++) image[i] = new bool[size+1];

	rasterizeArc(size);

	char filename[50];
#ifdef _WIN32
	sprintf_s(filename, 50, "circle%d.ppm", size);
#else
	sprintf(filename, "circle%d.ppm", size);
#endif

	ofstream outfile(filename);
	outfile << "P3\n# " << filename << "\n";
	outfile << size+1 << ' ' << size+1 << ' ' << 1 << endl;

	for (int i = 0; i <= size; i++)
	for (int j = 0; j <= size; j++)
		outfile << image[size-i][j] << " 0 0\n";

	// delete image data
	for (int i = 0; i <= size; i++) delete [] image[i];
	delete [] image;

	return 0;
}
