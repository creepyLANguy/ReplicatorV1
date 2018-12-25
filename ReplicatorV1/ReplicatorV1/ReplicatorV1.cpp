#include "stdafx.h"
#include <list>
#include <iostream>

using namespace std;

list<pair<int, int>> neighbour_calculator = 
{
  make_pair(-1,0),
  make_pair(+1,0),
  make_pair(0,-1),
  make_pair(0,+1),
  make_pair(-1,-1),
  make_pair(-1,+1),
  make_pair(+1,-1),
  make_pair(+1,+1),
};

enum State
{
  DEAD = 0,
  ALIVE = 1,
};


class Cell
{
public:

  int x;
  int y;

  list<Cell*> neighbours;

  State state;

  Cell(const int x, const int y, const State state = DEAD, Cell* creator = nullptr)
  {
    this->y = y;
    this->x = x;
    this->state = state;

    if (creator != nullptr)
    {
      neighbours.push_back(creator);
    }
  }

  int GetLivingNeighboursCount()
  {
    int counter = 0;
    for (Cell* c : neighbours)
    {
      if (c->state == ALIVE)
      {
        ++counter;
      }
    }
    return counter;
  }

};


class Grid
{
public:
  list<Cell*> cells;

  Cell* GetCell(const int x, const int y, const State state = DEAD, Cell* creator = nullptr)
  {
    for(Cell* c : cells)
    {
      //Cell already exists;
      if (c->x == x && c->y == y)
      {
        if (creator != nullptr)
        {
          c->neighbours.push_back(creator);
        }        

        return c;
      }
    }

    //Cell does not exist at this co-ordinate, so create and return it.
    Cell* newCell = new Cell(x, y, state, creator);
    cells.push_back(newCell);
    return newCell;
  }
};


void PrintGrid(Grid* grid, const int gen = -1)
{
  int shifter_x = 0;
  int shifter_y = 0;

  int max_x = 0;
  int max_y = 0;

  for (Cell* c : grid->cells)
  {
    if (c->x < 0)
    {
      const int abs_x = abs(c->x);
      if (abs_x > shifter_x)
      {
        shifter_x = abs_x;
      }
    }

    if (c->y < 0)
    {
      const int abs_y = abs(c->y);
      if (abs_y > shifter_y)
      {
        shifter_y = abs_y;
      }
    }

    if (c->x > max_x)
    {
      max_x = c->x;
    }

    if (c->y > max_y)
    {
      max_y = c->y;
    }

  }

  const int len_x = max_x + shifter_x + 1;
  const int len_y = max_y + shifter_y + 1;
  
  int** buff = new int*[len_x];
  for (int i = 0; i < len_x; ++i)
  {
    buff[i] = new int[len_y];
  }

  for (int i = 0; i < len_x; ++i)
  {
    for (int j = 0; j < len_y; ++j)
    {
      buff[i][j] = 0;
    }
  }
  
  
  for (Cell* c : grid->cells)
  {
    buff[c->x + shifter_x][c->y + shifter_y] = 1;
  }


  if (gen >= 0)
  {
    cout << "[" << (gen + 1) << "]" << "\r\n\r\n";
  }
  

  for (int i = 0; i < len_x; ++i)
  {
    for (int j = 0; j < len_y; ++j)
    {
      cout << buff[i][j];
    }
    cout << endl;
  }

  cout << endl;
}

Grid* GetNextGeneration(const Grid* grid)
{
  Grid* grid_temp = new Grid();
  for (Cell* c : grid->cells)
  {
    if (c->GetLivingNeighboursCount() % 2 == 1)
    {
      Cell* cell_temp = grid_temp->GetCell(c->x, c->y, ALIVE);
      grid_temp->cells.push_back(cell_temp);
    }
  }

  delete grid;
  return grid_temp;
}


void SetNeighboursForAllAliveCells(Grid* grid)
{
  for(Cell* c : grid->cells)
  {
    if (c->state == ALIVE)
    {
      for (auto p : neighbour_calculator)
      {
        c->neighbours.push_back(grid->GetCell(c->x + p.first, c->y + p.second, DEAD, c));
      }
    }
  }
}


void InitialiseGrid(Grid* grid)
{
  //grid->GetCell(0, 0, ALIVE);
  grid->GetCell(0, 0, ALIVE);
  grid->GetCell(1, 0, ALIVE);
  grid->GetCell(2, 0, ALIVE);
  grid->GetCell(2, 1, ALIVE);
  grid->GetCell(2, 2, ALIVE);
  grid->GetCell(1, 2, ALIVE);
  grid->GetCell(0, 2, ALIVE);
  grid->GetCell(0, 1, ALIVE);
  
  grid->GetCell(0, 0 + 4, ALIVE);
  grid->GetCell(1, 0 + 4, ALIVE);
  grid->GetCell(2, 0 + 4, ALIVE);
  grid->GetCell(2, 1 + 4, ALIVE);
  grid->GetCell(2, 2 + 4, ALIVE);
  grid->GetCell(1, 2 + 4, ALIVE);
  grid->GetCell(0, 2 + 4, ALIVE);
  grid->GetCell(0, 1 + 4, ALIVE);

  grid->GetCell(0, 0 + 4 + 4, ALIVE);
  grid->GetCell(1, 0 + 4 + 4, ALIVE);
  grid->GetCell(2, 0 + 4 + 4, ALIVE);
  grid->GetCell(2, 1 + 4 + 4, ALIVE);
  grid->GetCell(2, 2 + 4 + 4, ALIVE);
  grid->GetCell(1, 2 + 4 + 4, ALIVE);
  grid->GetCell(0, 2 + 4 + 4, ALIVE);
  grid->GetCell(0, 1 + 4 + 4, ALIVE);

  grid->GetCell(0 + 4, 0, ALIVE);
  grid->GetCell(1 + 4, 0, ALIVE);
  grid->GetCell(2 + 4, 0, ALIVE);
  grid->GetCell(2 + 4, 1, ALIVE);
  grid->GetCell(2 + 4, 2, ALIVE);
  grid->GetCell(1 + 4, 2, ALIVE);
  grid->GetCell(0 + 4, 2, ALIVE);
  grid->GetCell(0 + 4, 1, ALIVE);

  grid->GetCell(0 + 4 + 4, 0, ALIVE);
  grid->GetCell(1 + 4 + 4, 0, ALIVE);
  grid->GetCell(2 + 4 + 4, 0, ALIVE);
  grid->GetCell(2 + 4 + 4, 1, ALIVE);
  grid->GetCell(2 + 4 + 4, 2, ALIVE);
  grid->GetCell(1 + 4 + 4, 2, ALIVE);
  grid->GetCell(0 + 4 + 4, 2, ALIVE);
  grid->GetCell(0 + 4 + 4, 1, ALIVE);
  


}


void main()
{
  Grid* grid = new Grid();

  InitialiseGrid(grid);

  const int iterations = 10;

  for (int i = 0; i < iterations; ++i)
  {
    PrintGrid(grid, i);

    SetNeighboursForAllAliveCells(grid);
    grid = GetNextGeneration(grid);
    
    if (grid->cells.size() == 0)
    {
      return;
    }
  }
}

