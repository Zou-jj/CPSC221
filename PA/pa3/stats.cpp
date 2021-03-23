#include "stats.h"


#include "stats.h"

stats::stats(PNG & im){
    /* Your code here!! */
    sumRed = vector<vector<long>>(im.width(), vector<long>(im.height()));
    sumGreen = vector<vector<long>>(im.width(), vector<long>(im.height()));
    sumBlue = vector<vector<long>>(im.width(), vector<long>(im.height()));
    sumsqRed = vector<vector<long>>(im.width(), vector<long>(im.height()));
    sumsqGreen = vector<vector<long>>(im.width(), vector<long>(im.height()));
    sumsqBlue = vector<vector<long>>(im.width(), vector<long>(im.height()));
    for (int currX = 0; currX < im.width(); currX++){
        for (int currY = 0; currY < im.height(); currY++){
            if (currX == 0){
                if (currY == 0){
                    sumRed[currX][currY] = im.getPixel(currX, currY)->r;
                    sumGreen[currX][currY] = im.getPixel(currX, currY)->g;
                    sumBlue[currX][currY] = im.getPixel(currX, currY)->b;
                    sumsqRed[currX][currY] = im.getPixel(currX, currY)->r * im.getPixel(currX, currY)->r;
                    sumsqGreen[currX][currY] = im.getPixel(currX, currY)->g * im.getPixel(currX, currY)->g;
                    sumsqBlue[currX][currY] = im.getPixel(currX, currY)->b * im.getPixel(currX, currY)->b;
                } else {
                    sumRed[currX][currY] = im.getPixel(currX, currY)->r + sumRed[currX][currY - 1];
                    sumGreen[currX][currY] = im.getPixel(currX, currY)->g + sumGreen[currX][currY - 1];
                    sumBlue[currX][currY] = im.getPixel(currX, currY)->b + sumBlue[currX][currY - 1];
                    sumsqRed[currX][currY] = im.getPixel(currX, currY)->r * im.getPixel(currX, currY)->r + sumsqRed[currX][currY - 1];
                    sumsqGreen[currX][currY] = im.getPixel(currX, currY)->g * im.getPixel(currX, currY)->g + sumsqGreen[currX][currY - 1];
                    sumsqBlue[currX][currY] = im.getPixel(currX, currY)->b * im.getPixel(currX, currY)->b + sumsqBlue[currX][currY - 1];
                }
            } else {
                if (currY == 0){
                    sumRed[currX][currY] = im.getPixel(currX, currY)->r + sumRed[currX - 1][currY];
                    sumGreen[currX][currY] = im.getPixel(currX, currY)->g + sumGreen[currX - 1][currY];
                    sumBlue[currX][currY] = im.getPixel(currX, currY)->b + sumBlue[currX - 1][currY];
                    sumsqRed[currX][currY] = im.getPixel(currX, currY)->r * im.getPixel(currX, currY)->r + sumsqRed[currX - 1][currY];
                    sumsqGreen[currX][currY] = im.getPixel(currX, currY)->g * im.getPixel(currX, currY)->g + sumsqGreen[currX - 1][currY];
                    sumsqBlue[currX][currY] = im.getPixel(currX, currY)->b * im.getPixel(currX, currY)->b + sumsqBlue[currX - 1][currY];
                } else {
                    sumRed[currX][currY] = im.getPixel(currX, currY)->r + sumRed[currX][currY - 1] + sumRed[currX - 1][currY] - sumRed[currX - 1][currY - 1];
                    sumGreen[currX][currY] = im.getPixel(currX, currY)->g + sumGreen[currX][currY - 1] + sumGreen[currX - 1][currY] - sumGreen[currX - 1][currY - 1];
                    sumBlue[currX][currY] = im.getPixel(currX, currY)->b + sumBlue[currX][currY - 1] + sumBlue[currX - 1][currY] - sumBlue[currX - 1][currY - 1];
                    sumsqRed[currX][currY] = im.getPixel(currX, currY)->r * im.getPixel(currX, currY)->r + sumsqRed[currX][currY - 1] + sumsqRed[currX - 1][currY] - sumsqRed[currX - 1][currY - 1];
                    sumsqGreen[currX][currY] = im.getPixel(currX, currY)->g * im.getPixel(currX, currY)->g + sumsqGreen[currX][currY - 1] + sumsqGreen[currX - 1][currY] - sumsqGreen[currX - 1][currY - 1];
                    sumsqBlue[currX][currY] = im.getPixel(currX, currY)->b * im.getPixel(currX, currY)->b + sumsqBlue[currX][currY - 1] + sumsqBlue[currX - 1][currY] - sumsqBlue[currX - 1][currY - 1];
                }
            }
            // printf("sumRed[%d][%d]: %d  ", currX, currY, sumRed[currX][currY]);
        }
        // cout << endl;
    }
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
    /* Your code here!! */
    if (channel == 'r'){
        if (ul.first == 0){
            if (ul.second == 0){
                return sumRed[ul.first + w - 1][ul.second + h - 1];
            } else {
                return sumRed[ul.first + w - 1][ul.second + h - 1] - sumRed[ul.first + w - 1][ul.second - 1];
            }
        } else {
            if (ul.second == 0){
                return sumRed[ul.first + w - 1][ul.second + h - 1] - sumRed[ul.first - 1][ul.second + h - 1];
            } else {
                return sumRed[ul.first + w - 1][ul.second + h - 1] - sumRed[ul.first + w - 1][ul.second - 1] - sumRed[ul.first - 1][ul.second + h - 1] + sumRed[ul.first - 1][ul.second - 1];
            }
        }
    } else if (channel == 'g'){
        if (ul.first == 0){
            if (ul.second == 0){
                return sumGreen[ul.first + w - 1][ul.second + h - 1];
            } else {
                return sumGreen[ul.first + w - 1][ul.second + h - 1] - sumGreen[ul.first + w - 1][ul.second - 1];
            }
        } else {
            if (ul.second == 0){
                return sumGreen[ul.first + w - 1][ul.second + h - 1] - sumGreen[ul.first - 1][ul.second + h - 1];
            } else {
                return sumGreen[ul.first + w - 1][ul.second + h - 1] - sumGreen[ul.first + w - 1][ul.second - 1] - sumGreen[ul.first - 1][ul.second + h - 1] + sumGreen[ul.first - 1][ul.second - 1];
            }
        }
    } else {
        if (ul.first == 0){
            if (ul.second == 0){
                return sumBlue[ul.first + w - 1][ul.second + h - 1];
            } else {
                return sumBlue[ul.first + w - 1][ul.second + h - 1] - sumBlue[ul.first + w - 1][ul.second - 1];
            }
        } else {
            if (ul.second == 0){
                return sumBlue[ul.first + w - 1][ul.second + h - 1] - sumBlue[ul.first - 1][ul.second + h - 1];
            } else {
                return sumBlue[ul.first + w - 1][ul.second + h - 1] - sumBlue[ul.first + w - 1][ul.second - 1] - sumBlue[ul.first - 1][ul.second + h - 1] + sumBlue[ul.first - 1][ul.second - 1];
            }
        }
    }
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
    /* Your code here!! */
    if (channel == 'r'){
        if (ul.first == 0){
            if (ul.second == 0){
                return sumsqRed[ul.first + w - 1][ul.second + h - 1];
            } else {
                return sumsqRed[ul.first + w - 1][ul.second + h - 1] - sumsqRed[ul.first + w - 1][ul.second - 1];
            }
        } else {
            if (ul.second == 0){
                return sumsqRed[ul.first + w - 1][ul.second + h - 1] - sumsqRed[ul.first - 1][ul.second + h - 1];
            } else {
                return sumsqRed[ul.first + w - 1][ul.second + h - 1] - sumsqRed[ul.first + w - 1][ul.second - 1] - sumsqRed[ul.first - 1][ul.second + h - 1] + sumsqRed[ul.first - 1][ul.second - 1];
            }
        }
    } else if (channel == 'g'){
        if (ul.first == 0){
            if (ul.second == 0){
                return sumsqGreen[ul.first + w - 1][ul.second + h - 1];
            } else {
                return sumsqGreen[ul.first + w - 1][ul.second + h - 1] - sumsqGreen[ul.first + w - 1][ul.second - 1];
            }
        } else {
            if (ul.second == 0){
                return sumsqGreen[ul.first + w - 1][ul.second + h - 1] - sumsqGreen[ul.first - 1][ul.second + h - 1];
            } else {
                return sumsqGreen[ul.first + w - 1][ul.second + h - 1] - sumsqGreen[ul.first + w - 1][ul.second - 1] - sumsqGreen[ul.first - 1][ul.second + h - 1] + sumsqGreen[ul.first - 1][ul.second - 1];
            }
        }
    } else {
        if (ul.first == 0){
            if (ul.second == 0){
                return sumsqBlue[ul.first + w - 1][ul.second + h - 1];
            } else {
                return sumsqBlue[ul.first + w - 1][ul.second + h - 1] - sumsqBlue[ul.first + w - 1][ul.second - 1];
            }
        } else {
            if (ul.second == 0){
                return sumsqBlue[ul.first + w - 1][ul.second + h - 1] - sumsqBlue[ul.first - 1][ul.second + h - 1];
            } else {
                return sumsqBlue[ul.first + w - 1][ul.second + h - 1] - sumsqBlue[ul.first + w - 1][ul.second - 1] - sumsqBlue[ul.first - 1][ul.second + h - 1] + sumsqBlue[ul.first - 1][ul.second - 1];
            }
        }
    }
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
    /* Your code here!! */
    double varR = getSumSq('r', ul, w, h) - (getSum('r', ul, w, h)) * (getSum('r', ul, w, h)) / (w * h);
    double varG = getSumSq('g', ul, w, h) - (getSum('g', ul, w, h)) * (getSum('g', ul, w, h)) / (w * h);
    double varB = getSumSq('b', ul, w, h) - (getSum('b', ul, w, h)) * (getSum('b', ul, w, h)) / (w * h);
    // printf("sumsq: %d, sum: %d, sqsum: %d", getSumSq('r', ul, w, h), (getSum('r', ul, w, h) / (w * h)), ((getSum('r', ul, w, h) / (w * h)) * (getSum('r', ul, w, h) / (w * h))));
    return varR + varG + varB;
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
    /* Your code here!! */
    int r = getSum('r', ul, w, h) / (w * h);
    // printf("R avg: %d", r);
    int g = getSum('g', ul, w, h) / (w * h);
    // printf("G avg: %d", g);
    int b = getSum('b', ul, w, h) / (w * h);
    // printf("B avg: %d", b);
    RGBAPixel p = *(new RGBAPixel(r, g, b));
    return p;
}
