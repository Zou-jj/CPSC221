#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

/* YOUR CODE HERE */
    
}

PNG decoder::renderSolution(){

/* YOUR CODE HERE */

}

PNG decoder::renderMaze(){

/* YOUR CODE HERE */

}

void decoder::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */

}

pair<int,int> decoder::findSpot(){

/* YOUR CODE HERE */

}

int decoder::pathLength(){

/* YOUR CODE HERE */

}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */

}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */

}


bool decoder::compare(RGBAPixel p, int d){

/* YOUR CODE HERE */

}
