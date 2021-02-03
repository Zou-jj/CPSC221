#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  return data.size();
}

int Block::width() const {
  return data[0].size();
}

void Block::render(PNG &im, int x) const {
  for (int widthIndex = 0; widthIndex < width(); widthIndex++){
    for (int heightIndex = 0; heightIndex < im.height(); heightIndex++){
      *im.getPixel(x+widthIndex, heightIndex) = data[x+widthIndex][heightIndex];
    }
  }
}

void Block::build(PNG &im, int x, int width) {
  for (int widthIndex = 0; widthIndex < width; widthIndex++){
    for (int heightIndex = 0; heightIndex < im.height(); heightIndex++){
      data[x+widthIndex][heightIndex] = *im.getPixel(x+widthIndex, heightIndex);
    }
  }
}
