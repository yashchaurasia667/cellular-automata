#include "automata.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

enum states
{
  ON,
  DYING,
  OFF
};

std::vector<std::vector<int>> cells;

void init(int width, int height)
{
  std::srand(std::time(0));
  cells.assign(height, std::vector<int>(width, ON));
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      cells[i][j] = std::rand() % 3;
}

int getOnNeighbors(int i, int j)
{
  int on = 0;
  int rows = cells.size();
  int cols = cells[0].size();

  for (int di = -1; di <= 1; di++)
  {
    for (int dj = -1; dj <= 1; dj++)
    {
      if (di == 0 && dj == 0)
        continue;

      // wrap around edges
      int ni = (i + di + rows) % rows;
      int nj = (j + dj + cols) % cols;

      if (cells[ni][nj] == ON)
        on++;
    }
  }
  return on;
}

void briansBrain()
{
  auto next = cells;
  for (int i = 0; i < cells.size(); i++)
  {
    for (int j = 0; j < cells[i].size(); j++)
    {
      switch (cells[i][j])
      {
      case ON:
        next[i][j] = DYING;
        break;
      case OFF:
        // - A cell turns on if it was off but has *exactly* 2 neighbors that are on
        if (getOnNeighbors(i, j) == 2)
          next[i][j] = ON;
        break;
      case DYING:
        next[i][j] = OFF;
        break;

      default:
        break;
      }
    }
  }

  cells = next;
}

int getNeighborAverage(int i, int j)
{
  int average = 0;
  int rows = cells.size(), cols = cells[i].size();

  for (int di = -1; di <= 1; di++)
    for (int dj = -1; dj <= 1; dj++)
    {
      if (di == 0 && dj == 0)
        continue;

      int ni = (i + di + rows) % rows;
      int nj = (j + dj + cols) % cols;

      average += cells[ni][nj];
    }

  return average / 8;
}

void zhabotinsky(int num_states, int g)
{
  auto next = cells;
  for (int y = 0; y < cells.size(); y++)
  {
    for (int x = 0; x < cells[y].size(); x++)
    {
      if (cells[y][x] == 0)
        next[y][x] = (getNeighborAverage(y, x) + g) % num_states;
      else if (cells[y][x] == num_states - 1)
        next[y][x] = 0;
      else if (cells[y][x] > 0 && cells[y][x] < num_states)
        next[y][x] = getNeighborAverage(y, x);
      else
        next[y][x] = cells[y][x] + 1;
    }
  }
  cells = next;
}

#ifdef STANDALONE
int main()
{
  int side = 10;
  init(side, side);

  int count = 0;
  while (count++ < 50)
  {
    for (int i = 0; i < side; i++)
    {
      for (int j = 0; j < side; j++)
      {
        std::cout << cells[i][j] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    briansBrain();
  }
  return 0;
}
#endif