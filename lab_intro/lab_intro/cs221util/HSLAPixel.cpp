/**
 * @file HSLAPixel.cpp
 * Implementation of a HSLAPixel class
 *
 * @author Jiajun Zou
 */

#include "HSLAPixel.h"

using namespace std;

namespace cs221util {
  HSLAPixel::HSLAPixel() {
    s = 0;
    l = 1;
    a = 1;
  }

  HSLAPixel::HSLAPixel(int hue, double saturation, double luminance) {
    h = hue;
    s = saturation;
    l = luminance;
  }

  HSLAPixel::HSLAPixel(int hue, double saturation, double luminance, double alpha) {
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
  }
}
