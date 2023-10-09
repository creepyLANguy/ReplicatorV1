#ifndef CELL_H
#define CELL_H

#include <list>

using namespace std;

enum State
{
  DEAD = 0,
  ALIVE = 1,
};

enum SelfCountRule
{
  SELF_EXCLUDE = 0,
  SELF_INCLUDE = 1,
};


class Cell
{
private:

  list<Cell*> neighbours;

  int x;
  int y;

  State state;

  int baseCount;

public:

  Cell
  (
    const int x_in, 
    const int y_in, 
    const State state_in = DEAD, 
    const int baseCount_in = SELF_EXCLUDE, 
    Cell* creator = nullptr
  )
    :
    x(x_in),
    y(y_in),
    state(state_in),
    baseCount(baseCount_in)
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
  }

  void AddNeighbour(Cell* cell)
  {
    neighbours.push_back(cell);
  }

  int GetLivingNeighboursCount()
  {
    int counter = baseCount;

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

#endif // CELL_H
