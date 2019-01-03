#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

#include "Grid.h"

namespace
{
///////////////////////////////////////////////////////////////////////////////

const char* character_dead = " ";
const char* character_alive = ".";

const char* NL = "\r\n";

///////////////////////////////////////////////////////////////////////////////

void PrintGrid
  (
    Grid* grid, 
    const int gen = -1, 
    const char* character_alive_in = character_alive, 
    const char* character_dead_in = character_dead
  )
{
  const char* character_alive_final = character_alive_in;
  const char* character_dead_final = character_dead_in;

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
      const char* character = buff[i][j] == DEAD ? character_dead_final : character_alive_final;
      cout << character;
    }
    cout << NL;
  }

  cout << NL << NL << NL;


  for (int i = 0; i < len_x; ++i)
  {
    delete[] buff[i];
  }
  delete[] buff;
}

///////////////////////////////////////////////////////////////////////////////
}
#endif // UTILITIES_H
