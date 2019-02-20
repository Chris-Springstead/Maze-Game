#include "Maze.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Maze::can_move_to_tile(Position pos)
{
  // implement this function
  //adding up total number of col and rows
  int row_num = -1;
  int col_num;
  for (auto row : tiles){
    col_num = -1;
    row_num = row_num + 1;
    for (auto elem : row){
      ++col_num;
    }
  }
  //checking if new pos is a vaild pos in maze
  if (pos.row > row_num || pos.row < 0){
    return false;
  }
  else if (pos.col > col_num || pos.col < 0){
    return false;
  }
  else {
    //checking if wall
    if (tiles[pos.row][pos.col]->try_walk() == false)
      return false;
    else return true;
  }
}

bool Maze::is_tile_end(Position pos)
{
  return tiles[pos.row][pos.col]->is_end();
}

// print a maze
ostream & operator << (ostream &out, Maze &m)
{
  for(auto row : m.get_tiles()) {
    for(auto t : row)
      out << *t;

    out << endl;
  }

  return out;
}

// read in a maze from input
istream & operator >> (istream &in,  Maze &m)
{
  string row;
  while(getline(in, row)) {

    stringstream ss(row);
    vector<Tile*> tile_row;
    Tile* t;
    while(ss >> t) tile_row.push_back(t);

    // for (int i=0; i<tile_row.size(); i++)
    //  cout << tile_row[i]->tile_char << endl;
    
    m.get_tiles().push_back(tile_row);
  }

  return in;
}
