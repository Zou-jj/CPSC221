/**
 * @file HSLAPixel.h
 *
 * @author Jiajun Zou
 */

#ifndef HSLAPIXEL_H
#define HSLAPIXEL_H

namespace cs221util {
  class HSLAPixel {
  public:
    int h;
    double s;
    double l;
    double a;

    HSLAPixel();

    HSLAPixel(int hue, double saturation, double luminance);

    HSLAPixel(int hue, double saturation, double luminance, double alpha);
  };
}

#endif
