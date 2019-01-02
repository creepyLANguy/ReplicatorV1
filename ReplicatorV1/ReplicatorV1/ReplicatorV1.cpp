#include "stdafx.h"

using namespace std;

const int iterations = 32;

enum RuleSet
{
  SELF_EXCLUDE = 0,
  SELF_INCLUDE = 1,
};
const int ruleset = SELF_EXCLUDE;
//const int ruleset = SELF_INCLUDE;

enum Neighbourhood
{
  MOORE       = 0,
  VONNEUMANN  = 1,
  ALTAMISH    = 2,

  LAST
};
const int neighbourhood_type = MOORE;
//const int neighbourhood_type = VONNEUMANN;
//const int neighbourhood_type = ALTAMISH;

const char* character_dead  = " ";
const char* character_alive = ".";

const char* NL = "\r\n";

typedef list<pair<int, int>> NeighbourHood;

NeighbourHood neighbourhood_moore =
{
  make_pair(-1, +0),
  make_pair(+1, +0),
  make_pair(+0, -1),
  make_pair(+0, +1),
  make_pair(-1, -1),
  make_pair(-1, +1),
  make_pair(+1, -1),
  make_pair(+1, +1),
};

NeighbourHood neighbourhood_vonneumann =
{
  make_pair(-1, +0),
  make_pair(+1, +0),
  make_pair(+0, -1),
  make_pair(+0, +1),
};

NeighbourHood neighbourhood_altamish =
{
  make_pair(-1, -1),
  make_pair(-1, +1),
  make_pair(+1, -1),
  make_pair(+1, +1),
};

NeighbourHood neighbourhood_collection[LAST] = 
{ 
  neighbourhood_moore, 
  neighbourhood_vonneumann, 
  neighbourhood_altamish 
};

enum State
{
  DEAD = 0,
  ALIVE = 1,
};

///////////////////////////////////////////////////////////////////////////////

class Cell
{
private:

  list<Cell*> neighbours;

  int x;
  int y;

  State state;

public:

  Cell(const int x_in, const int y_in, const State state_in = DEAD, Cell* creator = nullptr) 
  : 
  x(x_in),
  y(y_in),
  state(state_in)
  {
    if (creator != nullptr)
    {
      neighbours.push_back(creator);
    }
  }

  int GetX() const
  {
    return x;
  }

  int GetY() const
  {
    return y;
  }

  State GetState() const
  {
    return state;
  };

  void AddNeighbour(Cell* cell)
  {
    neighbours.push_back(cell);
  }

  int GetLivingNeighboursCount()
  {
    int counter = ruleset; 

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

///////////////////////////////////////////////////////////////////////////////

class Grid
{
public:
  list<Cell*> cells;

  Cell* GetCell(const int x, const int y, const State state = DEAD, Cell* creator = nullptr)
  {
    for(Cell* c : cells)
    {
      //Cell already exists.
      if (c->GetX() == x && c->GetY() == y)
      {
        if (creator != nullptr)
        {
          c->AddNeighbour(creator);
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

///////////////////////////////////////////////////////////////////////////////

void PrintGrid(Grid* grid, const int gen = -1)
{
  int shifter_x = 0;
  int shifter_y = 0;

  int max_x = 0;
  int max_y = 0;

  for (Cell* c : grid->cells)
  {
    const int x = c->GetX();
    const int y = c->GetX();

    if (x < 0)
    {
      const int abs_x = abs(x);
      if (abs_x > shifter_x)
      {
        shifter_x = abs_x;
      }
    }

    if (y < 0)
    {
      const int abs_y = abs(y);
      if (abs_y > shifter_y)
      {
        shifter_y = abs_y;
      }
    }

    if (x > max_x)
    {
      max_x = x;
    }

    if (y > max_y)
    {
      max_y = y;
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
    buff[c->GetX() + shifter_x][c->GetY() + shifter_y] = 1;
  }


  if (gen >= 0)
  {
    cout << "[" << gen << "]" << NL << NL;
  }
  

  for (int i = 0; i < len_x; ++i)
  {
    for (int j = 0; j < len_y; ++j)
    {
      const char* character = buff[i][j] == DEAD ? character_dead : character_alive;
      cout << character;
    }
    cout << NL;
  }

  cout << NL << NL << NL ;
}

///////////////////////////////////////////////////////////////////////////////

Grid* GetNextGeneration(const Grid* grid)
{
  Grid* grid_temp = new Grid();
  for (Cell* c : grid->cells)
  {
    if (c->GetLivingNeighboursCount() % 2 == 1)
    {
      grid_temp->GetCell(c->GetX(), c->GetY(), ALIVE);
    }
  }

  delete grid;
  return grid_temp;
}

///////////////////////////////////////////////////////////////////////////////

void SetNeighboursForAllAliveCells(Grid* grid)
{
  for(Cell* c : grid->cells)
  {
    if (c->GetState() == ALIVE)
    {
      for (const auto p : neighbourhood_collection[neighbourhood_type])
      {
        Cell* cell = grid->GetCell(c->GetX() + p.first, c->GetY() + p.second, DEAD, c);
        c->AddNeighbour(cell);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void InitialiseGrid(Grid* grid)
{
  grid->GetCell(0, 0, ALIVE);
}

///////////////////////////////////////////////////////////////////////////////

void main()
{
  Grid* grid = new Grid();

  InitialiseGrid(grid);

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
