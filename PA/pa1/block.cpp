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
  for (unsigned int heightIndex = 0; heightIndex < im.height(); heightIndex++){
    for (int widthIndex = 0; widthIndex < width(); widthIndex++){
      *(im.getPixel(x+widthIndex, heightIndex)) = data[heightIndex][widthIndex];
    }
  }
}

void Block::build(PNG &im, int x, int width) {
  data = vector<vector<HSLAPixel>>(width);
  for (unsigned int heightIndex = 0; heightIndex < im.height(); heightIndex++){
    data[heightIndex] = vector<HSLAPixel>(im.height());
    for (int widthIndex = 0; widthIndex < width; widthIndex++){
      data[heightIndex][widthIndex] = *(im.getPixel(x+widthIndex, heightIndex));
    }
  }
}
