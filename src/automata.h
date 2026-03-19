#pragma once
#include <vector>

extern std::vector<std::vector<int>> cells;
void init(int width, int height);
int getOnNeighbors(int i, int j);
void briansBrain();