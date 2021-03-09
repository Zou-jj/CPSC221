#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s):start(s),mapImg(tm) {

/* YOUR CODE HERE */
    visits = vector<vector<bool>>(mapImg.width(), vector<bool> (mapImg.height(), false));
    distances = vector<vector<int>>(mapImg.width(), vector<int> (mapImg.height(), 0));
    vector<vector<pair<int,int>>> origin(mapImg.width(), vector<pair<int,int>> (mapImg.height(), make_pair(0,0)));
    Queue<pair<int,int>> traversal;
    Stack<pair<int,int>> path;
    pair<int,int> max;
    pair<int,int> curr;
    
    visits[start.first][start.second] = true;
    distances[start.first][start.second] = 0;
    max = start;
    traversal.enqueue(start);
    while (!traversal.isEmpty()){
        curr = traversal.dequeue();
        for (pair<int,int> p : neighbors(curr)){
            if (good(visits, distances, curr, p)){
                visits[p.first][p.second] = true;
                distances[p.first][p.second] = distances[curr.first][curr.second] + 1;
                if (distances[p.first][p.second] >= distances[max.first][max.second]){
                    max = p;
                }
                origin[p.first][p.second] = curr;
                traversal.enqueue(p);
            }
        }
    }
    curr = max;
    while (curr != start){
        path.push(curr);
        curr = make_pair(origin[curr.first][curr.second].first, origin[curr.first][curr.second].second);
    }
    path.push(curr);
    while(!path.isEmpty()){
        pathPts.push_back(path.pop());
    }
}

PNG decoder::renderSolution(){

/* YOUR CODE HERE */
    PNG rSoln = PNG(mapImg);

    for (int index = 0; index < pathPts.size(); index++){
        RGBAPixel* p = rSoln.getPixel(pathPts.at(index).first, pathPts.at(index).second);
        p->r = 255;
        p->g = 0;
        p->b = 0;
    }
    return rSoln;
}

PNG decoder::renderMaze(){

/* YOUR CODE HERE */
    PNG rMaze = PNG(mapImg);
    visits = vector<vector<bool>>(mapImg.width(), vector<bool> (mapImg.height(), false));
    distances = vector<vector<int>>(mapImg.width(), vector<int> (mapImg.height(), 0));
    Queue<pair<int,int>> traversal;

    visits[start.first][start.second] = true;
    traversal.enqueue(start);
    while (!traversal.isEmpty()){
        pair<int,int> curr = traversal.dequeue();
        for (pair<int,int> p : neighbors(curr)){
            if (good(visits, distances, curr, p)){
                // cout << "br ";
                visits[p.first][p.second] = true;
                distances[p.first][p.second] = distances[curr.first][curr.second] + 1;
                setGrey(rMaze, p);
                traversal.enqueue(p);
            }
        }
    }
    for (int col = -3; col <= 3; col++){
        for (int row = -3; row <= 3; row++){
            int x = start.first + col;
            int y = start.second + row;
            if (x >= 0 && x < (int)mapImg.width() && y >= 0 && y < (int)mapImg.height()){
                RGBAPixel* p = rMaze.getPixel(x, y);
                p->b = 0;
                p->g = 0;
                p->r = 255;
            }
        }
    }
    return rMaze;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */
    RGBAPixel* p = im.getPixel(loc.first, loc.second);
    p->r = 2 * (p->r / 4);
    p->g = 2 * (p->g / 4);
    p->b = 2 * (p->b / 4);
}

pair<int,int> decoder::findSpot(){

/* YOUR CODE HERE */
    return pathPts.back();
}

int decoder::pathLength(){

/* YOUR CODE HERE */
    return pathPts.size();
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
    if (next.first >= 0 && next.first < (int)mapImg.width()){
        if (next.second >= 0 && next.second < (int)mapImg.height()){
            if (v[next.first][next.second] == false){
                return compare(*mapImg.getPixel(next.first, next.second), d[curr.first][curr.second]);
            }
        }
    }
    return false;
}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */
    vector<pair<int,int>> n;
    n.push_back(make_pair(curr.first - 1, curr.second));
    n.push_back(make_pair(curr.first, curr.second + 1));
    n.push_back(make_pair(curr.first + 1, curr.second));
    n.push_back(make_pair(curr.first, curr.second - 1));
    return n;
}


bool decoder::compare(RGBAPixel p, int d){

/* YOUR CODE HERE */
    return (d + 1) % 64 == (p.r % 4) * 16 + (p.g % 4) * 4 + (p.b % 4);
}
