// File:        pa3.cpp
// Author:      cs221 instructors
// Date:        2021-03-03
// Description: Partial test of PA3 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets

#include "sqtree.h"

int main() {

  // read in image
  PNG orig;
  // orig.readFromFile("images/orig/small1.png");
  /*
  orig.readFromFile("images/orig/small2.png");
  orig.readFromFile("images/orig/pacman.png");
  orig.readFromFile("images/orig/huckleberry_hound.png");
  orig.readFromFile("images/orig/rocky.png");
  orig.readFromFile("images/orig/rocky_bullwinkle.png");
  orig.readFromFile("images/orig/colour.png");
  orig.readFromFile("images/orig/klee-flora-on-sand.png");
  orig.readFromFile("images/orig/stanley-totem-poles.png");
  orig.readFromFile("images/orig/vert.png");
  */

  orig.readFromFile("images/orig/stanley-totem-poles.png");

  printf("w: %d, h: %d\n", orig.width(), orig.height());
  // printf("orig r: %d, g: %d, b: %d\n", orig.getPixel(2, 0)->r, orig.getPixel(2, 0)->g, orig.getPixel(2, 0)->b);
  // printf("orig r: %d, g: %d, b: %d\n", orig.getPixel(380, 380)->r, orig.getPixel(380, 380)->g, orig.getPixel(380, 380)->b);
  printf("b: %d\n", stats(orig).getAvg(make_pair(0, 0), 2, 2).b);
  printf("               varR: %lf\n", stats(orig).getVar(make_pair(3, 0), 1, 1));

  // use it to build a sqtree (try other tolerances)
  SQtree t(orig, 20000.0);

  // copy the tree (to show you can)
  // SQtree tCopy(t);

  // render the sqtree
  PNG pic = t.render();

  // write it out
  pic.writeToFile("images/out/test.png");

  return 0;
}
