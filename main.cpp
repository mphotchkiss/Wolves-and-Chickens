#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "state.h"
#include "gameState.h"
#include <vector>

using namespace std;

struct state readFile(string, string);
int declareMode(string);

void bfsSearch(struct state init, struct state goal);
void dfsSearch(struct state init, struct state goal);
void iddfsSearch(struct state init, struct state goal);
void astarSearch(struct state init, struct state goal);

int main(int argc, char ** argv) {
  try {
    if (argc != 5) {
      throw(invalid_argument("\nPlease provide 4 arguments: <initial state file> <goal state file> <mode> <output file>\nMode options...\n\tbfs: breadth-first search\n\tdfs: depth-first search\n\tiddfs: iterative deepening depth-first search\n\tastar: A-star search\n\n"));
    }
  }
  catch(const exception& e) {
    cout << "\nAn exception occurred while processing inputs:\n" << e.what();
  }

  struct state init = readFile(argv[1], "Initial");
  struct state goal = readFile(argv[2], "Goal");
  cout << endl << "Init:" << endl << "Left Bank:\t" << init.leftChickens << "," << init.leftWolves << "," << (init.boat==false) << endl;
  cout << "Right Bank:\t" << init.rightChickens << "," << init.rightWolves << "," << (init.boat==true) << endl;
  cout << endl << "Goal:" << endl << "Left Bank:\t" << goal.leftChickens << "," << goal.leftWolves << "," << (goal.boat==false) << endl;
  cout << "Right Bank:\t" << goal.rightChickens << "," << goal.rightWolves << "," << (goal.boat==true) << endl;
  
  int mode = declareMode(argv[3]);
  switch(mode) {
    case 0:
      bfsSearch(init, goal);
      break;
    case 1:
      dfsSearch(init, goal);
      break;
    case 2:
      iddfsSearch(init, goal);
      break;
    case 3:
      astarSearch(init, goal);
      break;
    default:
      return 0;
  }
  return 0;
}

void bfsSearch(struct state init, struct state goal) {
  cout << "Performing BFS..." << endl;

  //generate the root node
  gameState * s = new gameState(init);

  //initialize the explored map as empty
  map<string, bool> explored;
  
  //initialize the frontier with the initial state
  vector<gameState *> frontier;
  frontier.push_back(s);

  int expanded = 0;

  while (true) {
    if (frontier.empty()) {
      cout << "No solution" << endl;
      return;
    }
    else {
      s = frontier.back();
      explored.insert(pair<string, bool>(s->getStateKey(), true));
      frontier.pop_back();
      if (s->isWon(goal)) {
        cout << "Solution found!" << endl;
        return;
      }
      s->expand();
      gameState **children = s->getChildren();
      for (int i = 0; i < 5; i++) {
        if (children[i] == NULL)
          continue;
        else {
          expanded++;
          if (!explored[children[i]->getStateKey()])
            frontier.insert(frontier.begin(), children[i]);
        }
      }
    }
  }
  cout << "Solution found!" << endl;
}

void dfsSearch(struct state init, struct state goal) {
  cout << "Performing DFS..." << endl;
  gameState * s = new gameState(init);
}

void iddfsSearch(struct state init, struct state goal) {
  cout << "Performing IDDFS..." << endl;
  gameState * s = new gameState(init);
}

void astarSearch(struct state init, struct state goal) {
  cout << "Performing A*..." << endl;
  gameState * s = new gameState(init);
}

struct state readFile(string filePath, string state) {
  ifstream file;
  struct state s;
  string n;
  try {
    file.open(filePath);
    if (file.is_open()) {
      getline(file, n, ',');
      s.leftChickens = stoi(n);
      getline(file, n, ',');
      s.leftWolves = stoi(n);
      getline(file, n, '\n');
      s.boat = stoi(n) != 1;
      getline(file, n, ',');
      s.rightChickens = stoi(n);
      getline(file, n, ',');
      s.rightWolves = stoi(n);
      getline(file, n, '\n');
    }
    file.close();
  }
  catch(const exception& e) {
    cout << "\nAn exception occurred while processing the " << state << " state file: " << e.what();
  } 
  return s;
}

int declareMode(string mode) {
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
  catch(const exception& e){
    cout << "\nAn exception occurred while selecting the mode: " << e.what();
  }
  if (mode == "bfs")
    return 0;
  else if (mode == "dfs")
    return 1;
  else if (mode == "iddfs") 
    return 2;
  else if (mode == "astar")
    return 3;
  else
    return -1;
}
