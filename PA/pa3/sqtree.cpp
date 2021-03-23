/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  // Your code here.
  stats *st = new stats(imIn);
  pair <int,int> currPair = make_pair(0,0);
  // printf("________ iw: %d, ih: %d", imIn.width(), imIn.height());
  root = buildTree(*st, currPair, imIn.width(), imIn.height(), tol);
  // printf("________ w: %d, h: %d, iw: %d, ih: %d", root->width, root->height, imIn.width(), imIn.height());

  // printf("w: %d, h: %d", root->width, root->height);
  // PNG rendImg = PNG(imIn);
  // for (int x = 0; x < rendImg.width(); x++){
  //   for (int y = 0; y < rendImg.height(); y++){
  //     RGBAPixel* p = rendImg.getPixel(x, y);
  //     p->b = 0;
  //     p->g = 0;
  //     p->r = 255;
  //   }
  // }
  PNG rendImg = *(new PNG(root->width, root->height));
  queue<Node *> q;
  // int sum = 0;
  q.push(root);
  while(!q.empty()){
    Node *node = q.front();
    if (node->NW == NULL && node->NE == NULL && node->SW == NULL && node->SE == NULL){
      for (int offsetX = 0; offsetX < node->width; offsetX++){
        for (int offsetY = 0; offsetY < node->height; offsetY++){
          RGBAPixel* p = rendImg.getPixel(node->upLeft.first + offsetX, node->upLeft.second + offsetY);
          // if (sum == 1)
          // printf("set avg r: %d, g: %d, b: %d", node->avg.r, node->avg.g, node->avg.b);
          *p = node->avg;
          // printf("point at x: %d, y: %d\n", node->upLeft.first + offsetX, node->upLeft.second + offsetY);
          // printf("r: %d\n", p->r);
          // sum++;
        }
      }
    }
    q.pop();
    if (node->NW != NULL){
      q.push(node->NW);
    }
    if (node->NE != NULL){
      q.push(node->NE);
    }
    if (node->SW != NULL){
      q.push(node->SW);
    }
    if (node->SE != NULL){
      q.push(node->SE);
    }
  }
  // printf("rendered %d P\n", sum);
  // // rendImg.writeToFile("images/out/test.png");

  // rendImg.writeToFile("images/test.png");
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  // Your code here.
  Node* thisNode = new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
  double minMaxVar = s.getVar(ul, w, h);
  if ((w == 1 && h == 1) || minMaxVar < tol){
    // printf("returned avg: %d\n", s.getAvg(ul, w, h).r);
    return new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
  } else {
    pair <int,int> minMaxPair = ul;
    for (int currX = ul.first; currX < w + ul.first; currX++){
      for (int currY = ul.second; currY < h + ul.second; currY++){
        if (currX == ul.first){
          if (currY == ul.second){
            continue;
          } else {
            double upVar = s.getVar(ul, w, currY - ul.second);
            double downVar = s.getVar(make_pair(currX, currY), w, h - currY + ul.second);
            double maxVar = max(upVar, downVar);
            if (maxVar < minMaxVar){
              minMaxVar = maxVar;
              minMaxPair = make_pair(currX, currY);
            }
          }
        } else {
          if (currY == ul.second){
            double leftVar = s.getVar(ul, currX - ul.first, h);
            double rightVar = s.getVar(make_pair(currX, currY), w - currX + ul.first, h);
            double maxVar = max(leftVar, rightVar);
            if (maxVar < minMaxVar){
              minMaxVar = maxVar;
              minMaxPair = make_pair(currX, currY);
            }
          } else {
            double upLeftVar = s.getVar(ul, currX - ul.first, currY - ul.second);
            double upRightVar = s.getVar(make_pair(currX, ul.second), w - currX + ul.first, currY - ul.second);
            double downLeftVar = s.getVar(make_pair(ul.first, currY), currX - ul.first, h - currY + ul.second);
            double downRightVar = s.getVar(make_pair(currX, currY), w - currX + ul.first, h - currY + ul.second);
            double maxVar = max(upLeftVar, upRightVar);
            maxVar = max(maxVar, downLeftVar);
            maxVar = max(maxVar, downRightVar);
            if (maxVar < minMaxVar){
              minMaxVar = maxVar;
              minMaxPair = make_pair(currX, currY);
            }
          }
        }
        // printf("x: %d, y: %d, maxVar: %d\n", currX, currY, minMaxVar);
      }
    }
    // printf("current w: %d, h: %d\n", w, h);
    // printf("block at point --- x: %d, y: %d\n", ul.first, ul.second);
    // printf("split at point --- x: %d, y: %d\n", minMaxPair.first, minMaxPair.second);
    // printf("avg r: %d, g: %d, b: %d\n", s.getAvg(ul, w, h).r, s.getAvg(ul, w, h).g, s.getAvg(ul, w, h).b);

    if (minMaxPair.first == ul.first){
      // printf("b0");
      if (minMaxPair.second == ul.second){
        // printf("special case ----- w: %d, h: %d",w ,h);
        return thisNode;
      } else {
        // printf("b1\n");
        pair <int,int> upPair = ul;
        pair <int,int> downPair = minMaxPair;
        Node* upNode = buildTree(s, upPair, w, minMaxPair.second - ul.second, tol);
        Node* downNode = buildTree(s, downPair, w, h - minMaxPair.second + ul.second, tol);
        thisNode->NW = upNode;
        thisNode->SW = downNode;
        // printf("\n");
        return thisNode;
      }
    } else {
      if (minMaxPair.second == ul.second){
        // printf("b2\n");
        pair <int,int> leftPair = ul;
        pair <int,int> rightPair = minMaxPair;
        // printf("h: %d", h);
        Node* leftNode = buildTree(s, leftPair, minMaxPair.first - ul.first, h, tol);
        Node* rightNode = buildTree(s, rightPair, w - minMaxPair.first + ul.first, h, tol);
        thisNode->NW = leftNode;
        thisNode->SW = rightNode;
        // printf("\n");
        return thisNode;
      } else {
        // printf("b3\n");
        pair <int,int> upLeftPair = ul;
        pair <int,int> upRightPair = make_pair(minMaxPair.first, ul.second);
        pair <int,int> downLeftPair = make_pair(ul.first, minMaxPair.second);
        pair <int,int> downRightPair = minMaxPair;
        Node* upLeftNode = buildTree(s, upLeftPair, minMaxPair.first - ul.first, minMaxPair.second - ul.second, tol);
        Node* upRightNode = buildTree(s, upRightPair, w - minMaxPair.first + ul.first, minMaxPair.second - ul.second, tol);
        Node* downLeftNode = buildTree(s, downLeftPair, minMaxPair.first - ul.first, h - minMaxPair.second + ul.second, tol);
        Node* downRightNode = buildTree(s, downRightPair, w - minMaxPair.first + ul.first, h - minMaxPair.second + ul.second, tol);
        thisNode->NW = upLeftNode;
        thisNode->NE = upRightNode;
        thisNode->SW = downLeftNode;
        thisNode->SE = downRightNode;
        // printf("\n");
        return thisNode;
      }
    }
  }
}

/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  PNG rendImg = *(new PNG(root->width, root->height));
  queue<Node *> q;
  // int sum = 0;
  q.push(root);
  while(!q.empty()){
    Node *node = q.front();
    if (node->NW == NULL && node->NE == NULL && node->SW == NULL && node->SE == NULL){
      for (int offsetX = 0; offsetX < node->width; offsetX++){
        for (int offsetY = 0; offsetY < node->height; offsetY++){
          RGBAPixel* p = rendImg.getPixel(node->upLeft.first + offsetX, node->upLeft.second + offsetY);
          // if (sum == 1)
          // printf("set avg r: %d, g: %d, b: %d", node->avg.r, node->avg.g, node->avg.b);
          *p = node->avg;
          // printf("point at x: %d, y: %d\n", node->upLeft.first + offsetX, node->upLeft.second + offsetY);
          // printf("r: %d\n", p->r);
          // sum++;
        }
      }
    }
    q.pop();
    if (node->NW != NULL){
      q.push(node->NW);
    }
    if (node->NE != NULL){
      q.push(node->NE);
    }
    if (node->SW != NULL){
      q.push(node->SW);
    }
    if (node->SE != NULL){
      q.push(node->SE);
    }
  }
  return rendImg;
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  // Your code here.
}

void SQtree::copy(const SQtree & other) {
  // Your code here.
}

int SQtree::size() {
  // Your code here.
}

