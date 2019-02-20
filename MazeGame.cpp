// implementation of MazeGame functions

#include "MazeGame.h"

MazeGame::MazeGame(string filename)
{
  save_out.open(out_name);
  ifstream in;
  in.open(filename);
  if (!in) {
    cerr << "Wrong maze tiles file: " + filename << endl;
    throw IncorrectFile();
  }
  save_out << "Maze tiles file: " << filename << endl << endl;
  in >> maze;
}

MazeGame::~MazeGame()
{
  save_out.close();
}

void MazeGame::start_game(istream & is)
{
  // implement this function
  int row_num = 0;
  int start_tiles = 0;
  for (auto row : maze.get_tiles()){
    int location = 0;
    for (auto tiles : row){
      if (tiles->tile_char == 'S'){
        start_tiles += 1;
        Position pos(row_num,location);
        players.push_back(new MazePlayer(pos));
      }
      location += 1;
    }
    row_num += 1;
  }
  
  if (players.size() == start_tiles){
    print_maze();
    cout << '\n';
    save_out << '\n';
  }
  update_loop(is);
}

// Important: if you use cout << something
// do the same with save_out << something
// Otherwise, the file output.txt would be incorrect
void MazeGame::update_loop(istream & is)
{
  int pnum = 0; // player's number
  for(auto player : players) {
    pnum++;
    // implement code here
    cout << "Player " << pnum << " Position: " << player->get_position() << endl;
    cout << "Number of moves: " << player->move_number() << " ------" << endl;
    save_out << "Player " << pnum << " Position: " << player->get_position() << endl;
    save_out << "Number of moves: " << player->move_number() << " ------" << endl;
    
    Position new_pos;

    cout << "\nEnter desired move: \n";
    save_out << "\nEnter desired move: \n";
    string user_choice;
    cin >> user_choice;
    save_out << user_choice << endl;
    new_pos = player->take_turn(user_choice);

    if (maze.can_move_to_tile(new_pos) == true){
      player->set_position(new_pos);
    }
    else{
      while (true){
        cout << "Invalid move try again: " << endl;
        save_out << "Invalid move try again: " << endl;
        string try_again;
        cin >> try_again;
        save_out << try_again << endl;
        if (maze.can_move_to_tile(player->take_turn(try_again)) == true){
          player->set_position(player->take_turn(try_again));
          break;
        }
      }
    }
    if (maze.is_tile_end(player->get_position()) == true){
      cout << "\nPlayer " << pnum << " Won!\n";
      save_out << "\nPlayer " << pnum << " Won!\n";
      return;
    } 
    else{
      cout << '\n';
      save_out << '\n';
      print_maze(); 
      cout << '\n';
      save_out << '\n';
    }
  }
  update_loop(is);
}

void MazeGame::print_maze()
{
  vector<string> grid;
  for(auto row : maze.get_tiles()) {
    string tiles = "";
    for(auto t : row)
      tiles += t->tile_char;

    grid.push_back(tiles);
  }

  for(auto player : players)
    grid[player->get_position().row][player->get_position().col] = 'P';

  cout << " ";
  save_out << " ";

  for(int i = 0; i < grid[0].size(); i++) {
    cout << i;
    save_out << i;
  }

  cout << endl;
  save_out << endl;

  for(int i = 0; i < grid.size(); i++) {
    cout << i << grid[i] << endl;
    save_out << i << grid[i] << endl;
  }
}