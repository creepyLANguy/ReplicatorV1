#ifndef NEIGHBOURHOODS_H
#define NEIGHBOURHOODS_H

#include <list>

using namespace std;

typedef list<pair<int, int>> NeighbourHood;

enum Neighbourhood_Types
{
  MOORE = 0,
  VONNEUMANN = 1,
  ALTAMISH = 2,

  LAST
};

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

#endif // NEIGHBOURHOODS_H
