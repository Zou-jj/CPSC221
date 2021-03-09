#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{

/* YOUR CODE HERE */
    base = baseim;
    maze = mazeim;
    start = s;
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */
    RGBAPixel* p = im.getPixel(loc.first, loc.second);
    p->r = 2 * (p->r / 4);
    p->g = 2 * (p->g / 4);
    p->b = 2 * (p->b / 4);
    // RGBAPixel* p = im.getPixel(loc.first, loc.second);
    // p->r = d / 8;
    // p->g = d / 8;
    // p->b = d / 8;
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

/* YOUR CODE HERE */
    RGBAPixel* p = im.getPixel(loc.first, loc.second);
    p->r = (p->r & 0xFC) + ((d / 16) % 4);
    p->g = (p->g & 0xFC) + ((d / 4) % 4);
    p->b = (p->b & 0xFC) + (d % 4);
}

PNG treasureMap::renderMap(){

/* YOUR CODE HERE */
    PNG map = PNG(base);
    vector<vector<bool>> visits(base.width(), vector<bool> (base.height(), false));
    vector<vector<int>> distances(base.width(), vector<int> (base.height(), 0));
    Queue<pair<int,int>> traversal;
    
    visits[start.first][start.second] = true;
    distances[start.first][start.second] = 0;
    setLOB(map, start, 0);
    traversal.enqueue(start);
    while (!traversal.isEmpty()){
        pair<int,int> curr = traversal.dequeue();
        for (pair<int,int> p : neighbors(curr)){
            if (good(visits, curr, p)){
                visits[p.first][p.second] = true;
                distances[p.first][p.second] = distances[curr.first][curr.second] + 1;
                setLOB(map, p, distances[p.first][p.second]);
                traversal.enqueue(p);
            }
        }
    }
    return map;
}


PNG treasureMap::renderMaze(){

/* YOUR CODE HERE */
    PNG rMaze = PNG(base);
    vector<vector<bool>> visits(base.width(), vector<bool>(base.height()));
    Queue<pair<int,int>> traversal;

    visits[start.first][start.second] = true;
    traversal.enqueue(start);
    while (!traversal.isEmpty()){
        pair<int,int> curr = traversal.dequeue();
        for (pair<int,int> p : neighbors(curr)){
            if (good(visits, curr, p)){
                visits[p.first][p.second] = true;
                setGrey(rMaze, p);
                traversal.enqueue(p);
            }
        }
    }
    for (int col = -3; col <= 3; col++){
        for (int row = -3; row <= 3; row++){
            int x = start.first + col;
            int y = start.second + row;
            if (x >= 0 && x < (int)base.width() && y >= 0 && y < (int)base.height()){
                RGBAPixel* p = rMaze.getPixel(x, y);
                p->b = 0;
                p->g = 0;
                p->r = 255;
            }
        }
    }
    return rMaze;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
    if (next.first >= 0 && next.first < (int)base.width()){
        if (next.second >= 0 && next.second < (int)base.height()){
            if (v[next.first][next.second] == false){
                return maze.getPixel(next.first, next.second)->operator==(*maze.getPixel(curr.first, curr.second));
            }
        }
    }
    return false;
}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */
    vector<pair<int,int>> n;
    n.push_back(make_pair(curr.first - 1, curr.second));
    n.push_back(make_pair(curr.first, curr.second + 1));
    n.push_back(make_pair(curr.first + 1, curr.second));
    n.push_back(make_pair(curr.first, curr.second - 1));
    return n;
}
