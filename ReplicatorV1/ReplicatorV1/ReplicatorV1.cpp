#include "CA.h"

const int iterations = 32;

const bool terminateExecutionOnEmptyGrid = true;

const SelfCountRule selfCountRule = SELF_EXCLUDE;

const int neighbourhood_type = MOORE;

Grid* grid;

///////////////////////////////////////////////////////////////////////////////

Grid* GetNextGeneration()
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

void SetNeighboursForAllAliveCells()
{
  for(Cell* c : grid->cells)
  {
    if (c->GetState() == ALIVE)
    {
      for (const auto p : neighbourhood_collection[neighbourhood_type])
      {
        Cell* cell = grid->GetCell(c->GetX() + p.first, c->GetY() + p.second, DEAD, selfCountRule, c);
        c->AddNeighbour(cell);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void InitialiseGrid()
{
  grid->GetCell(0, 0, ALIVE);
}

///////////////////////////////////////////////////////////////////////////////

bool ShouldTerminateExecution()
{
  if (terminateExecutionOnEmptyGrid == true)
  {
    if (grid->cells.size() == 0)
    {
      return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////

void main()
{
  grid = new Grid();

  InitialiseGrid();

  for (int i = 0; i < iterations; ++i)
  {
    PrintGrid(grid, i);

    SetNeighboursForAllAliveCells();
    grid = GetNextGeneration();
    
    if (ShouldTerminateExecution() == true)
    {
      break;
    }
  }

  delete grid;
}
