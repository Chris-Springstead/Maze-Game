#ifndef TILE_H
#define TILE_H

#include <iostream>

using namespace std;

class Tile
{
public:
  char tile_char = '_';

public:
  virtual bool try_walk()
  {
    return false;
  }

  virtual bool is_start()
  {
    return false;
  }

  virtual bool is_end()
  {
    return false;
  }
};

class WallTile : public Tile
{
  // implement this class
public:
  WallTile(){
    tile_char = 'W';
  }
  virtual bool try_walk(){
      return false;
  }
};

class EmptyTile : public Tile
{
  // implement this class
public:
  EmptyTile(){
    tile_char = 'X';
  }
  virtual bool try_walk(){
      return true;
  }
};

class StartingTile : public EmptyTile
{
  // implement this class
public:
  StartingTile(){
    tile_char = 'S';
  }
  virtual bool is_start(){
      return true;
  }
};

class EndingTile : public EmptyTile
{
  // implement this class
public:
  EndingTile(){
    tile_char = 'E';
  }
  virtual bool is_end(){
      return true;
  }
};

ostream & operator << (ostream &out, const Tile &t);
istream & operator >> (istream &in,  Tile *&t);

#endif