#pragma once
#include "../include/grid.h"
#include <vector>
#include <cstdlib>
class Agent
{
public:
    Agent(Grid* grid); 
    ~Agent();

    void update();
    bool containsMovement(int x, int y);
private:
    Grid* grid_; 
    unsigned int x;
    unsigned int y;
    bool dirX;
    int extra;
    bool obstacleX;

};
