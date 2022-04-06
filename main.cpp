#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void readFile(string, string);
void declareState(string);

int main(int argc, char ** argv) {
  if (argc != 5) {
    cout << "\nPlease provide 4 arguments: <initial state file> <goal state file> <mode> <output file>";
    cout << "\nMode options...\n\tbfs: breadth-first search\n\tdfs: depth-first search\n\tiddfs: iterative deepening depth-first search\n\tastar: A-star search";
  }
  readFile(argv[1], "Initial");
  readFile(argv[2], "Goal");
  declareState(argv[3]);
  return 0;
}

void readFile(string filePath, string state) {
  ifstream file;
  string leftBank;
  string rightBank;
  try {
    file.open(filePath);
    if (file.is_open()) {
      file >> leftBank;
      file >> rightBank;
    }
    cout << "\n" << state << " Left Bank: " << leftBank;
    cout << "\n" << state << " Right Bank: " << rightBank << endl;
  }
  catch(const std::exception& e) {
    cout << "\nAn exception occurred while processing the " << state << " state file: " << e.what();
  } 
}

void declareState(string mode) {
  map<string, bool> modeMap;
  modeMap.insert(pair<string, bool>("bfs", true));
  modeMap.insert(pair<string, bool>("dfs", true));
  modeMap.insert(pair<string, bool>("iddfs", true));
  modeMap.insert(pair<string, bool>("astar", true));
  try {
    if (!modeMap[mode])
      throw(invalid_argument("Mode must be bfs, dfs, iddfs, or astar\n"));
    cout << "\nMode: " << mode << endl;
  }
  catch(const std::exception& e){
    cout << "\nAn exception occurred while selecting the mode: " << e.what();
  }
}
