#pragma once
#include <vector>

extern std::vector<std::vector<int>> cells;
void init(int width, int height);
int getOnNeighbors(int i, int j);
void briansBrain();
int getNeighborAverage(int i, int j);
void zhabotinsky(int num_states = 100, int g = 5);