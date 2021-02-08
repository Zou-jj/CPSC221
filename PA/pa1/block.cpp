#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  return data[0].size();
}

int Block::width() const {
  return data.size();
}

void Block::render(PNG &im, int x) const {
  for (int widthIndex = 0; widthIndex < width(); widthIndex++){
    for (unsigned int heightIndex = 0; heightIndex < im.height(); heightIndex++){
      *(im.getPixel(x+widthIndex, heightIndex)) = data[widthIndex][heightIndex];
    }
  }
}

void Block::build(PNG &im, int x, int width) {
  data = vector<vector<HSLAPixel>>(width);
  for (int widthIndex = 0; widthIndex < width; widthIndex++){
    data[widthIndex] = vector<HSLAPixel>(im.height());
    for (unsigned int heightIndex = 0; heightIndex < im.height(); heightIndex++){
      data[widthIndex][heightIndex] = *(im.getPixel(x+widthIndex, heightIndex));
    }
  }
}
