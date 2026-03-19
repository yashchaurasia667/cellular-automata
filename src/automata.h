#pragma once
#include <vector>

extern std::vector<std::vector<int>> cells;
void init(int width, int height);
void briansBrain();
void zhabotinsky(int num_states = 50, int g = 2);