#ifndef GRID_H
#define GRID_H

#include "Cell.h"

class Grid
{
public:
  list<Cell*> cells;

  Cell* GetCell
  (
    const int x,
    const int y,
    const State state = DEAD,
    const SelfCountRule selfCountRule = SELF_EXCLUDE,
    Cell* creator = nullptr
  )
  {
    for (Cell* c : cells)
    {
      //Cell already exists.
      if (c->GetX() == x && c->GetY() == y)
      {
        if (creator != nullptr)
        {
          //AL.
          //Comment this out if you wanna see trippy patterns :P
          c->AddNeighbour(creator);
        }

        return c;
      }
    }

    //Cell does not exist at this co-ordinate, so create and return it.
    Cell* newCell = new Cell(x, y, state, selfCountRule, creator);
    cells.push_back(newCell);
    return newCell;
  }

  ~Grid()
  {
    for (Cell* c : cells)
    {
      delete c;
      c = nullptr;
    }
  }

};

#endif // GRID_H
