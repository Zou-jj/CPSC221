
// File:        main.cpp
// Author:      cheeren
// Date:        2021-02-20
// Description: Partial test of PA2 functionality
//


#include "treasureMap.h"
#include "decoder.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{

	PNG maze;
	maze.readFromFile("images/zdesmaze.png");
	pair<int,int> start(69,359);

    PNG base;
    base.readFromFile("images/zdesbase.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	treasure.writeToFile("images/zdesembedded.png");
    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/zdesgreyedmaze.png");

    decoder dec(treasure,start);
    PNG soln = dec.renderSolution();
    PNG solnmaze = dec.renderMaze();

    soln.writeToFile("images/zdessoln.png");
    solnmaze.writeToFile("images/zdessolnmaze.png");

  return 0;
}
