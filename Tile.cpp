#include "Tile.h"

// output a tile character
ostream & operator << (ostream &out, const Tile &t)
{
  out << t.tile_char;
  return out;
}

// *& is a reference to a pointer
// here t is a reference to Tile*
// read in a tile character, and return in t a Tile object
istream & operator >> (istream &in,  Tile *&t)
{
  // implement this function
  char temp;
  in >> temp;
  //cout << temp << endl;
  // make construtor to force t's value onto the tile type?
  if (temp == 'W')
    t = new WallTile();
  if (temp == 'X')
    t = new EmptyTile();
  if (temp == 'S')
    t = new StartingTile();
  if (temp == 'E')
    t = new EndingTile();
  //cout << t->tile_char << endl;
  return in;
}