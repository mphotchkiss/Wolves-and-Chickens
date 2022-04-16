#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "state.h"
#include "gameState.h"
#include <vector>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <limits.h>

using namespace std;

struct state readFile(string, string);
int declareMode(string);

gameState * bfsSearch(struct state init, struct state goal, char * output_file);
gameState * dfsSearch(struct state init, struct state goal, char * output_file);
gameState * iddfsSearch(struct state init, struct state goal, char * output_file);
gameState * astarSearch(struct state init, struct state goal, char * output_file);
void writeSolution(string path, gameState * s);

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
  
  gameState * s;

  int mode = declareMode(argv[3]);
  switch(mode) {
    case 0:
      s = bfsSearch(init, goal, argv[4]);
      break;
    case 1:
      s = dfsSearch(init, goal, argv[4]);
      break;
    case 2:
      s = iddfsSearch(init, goal, argv[4]);
      break;
    case 3:
      s = astarSearch(init, goal, argv[4]);
      break;
    default:
      return 0;
  }
  return 0;
}

void printOutput(gameState * s, int expanded, char * output_file)
{
  int path_length = -1;
  ofstream fout;
  fout.open(output_file);
  while (s != NULL)
  {
    path_length++;
    fout << "Left Bank: ";
    fout << s->getState().rightChickens;
    fout << " Chickens, ";
    fout << s->getState().rightWolves;
    fout << " Wolves, ";
    fout << int(s->getState().boat);
    fout << " Boat\n";
    fout << "Right Bank: ";
    fout << s->getState().leftChickens;
    fout << " Chickens, ";
    fout << s->getState().leftWolves;
    fout << " Wolves, ";
    fout << int(!s->getState().boat);
    fout << " Boat\n\n";

    cout << "Left Bank: ";
    cout << s->getState().rightChickens;
    cout << " Chickens, ";
    cout << s->getState().rightWolves;
    cout << " Wolves, ";
    cout << int(s->getState().boat);
    cout << " Boat\n";
    cout << "Right Bank: ";
    cout << s->getState().leftChickens;
    cout << " Chickens, ";
    cout << s->getState().leftWolves;
    cout << " Wolves, ";
    cout << int(!s->getState().boat);
    cout << " Boat\n\n";

    s = s->getParent();
  }
  fout << "Nodes Expanded: ";
  fout << expanded << endl;
  fout << "\nPath Length: ";
  fout << path_length << endl;

  cout << "Nodes Expanded: ";
  cout << expanded << endl;
  cout << "\nPath Length: ";
  cout << path_length << endl;
}

gameState * bfsSearch(struct state init, struct state goal, char * output_file) {
  cout << "Performing BFS..." << endl;

  int expanded = 0;

  //generate the root node
  gameState * s = new gameState(init, goal);

  //initialize the explored map as empty
  map<string, bool> explored;
  map<string, bool> frontierMap;
  
  //initialize the frontier with the initial state
  //vector<gameState *> test_frontier;
  queue<gameState *> frontier;
  frontier.push(s);
  //test_frontier.push_back(s);

  while (true) {
    if (frontier.empty()) {
      cout << "no solution found" << endl;
      return NULL;
    }
    else {
      s = frontier.front();
      frontier.pop();
      explored.insert(pair<string, bool>(s->getStateKey(), true));
      //cout << "frontier:" << endl;
      // for (int i = 0; i < test_frontier.size(); i++) {
      //   test_frontier[i]->printState();
      // }
      //cout << endl;
      //test_frontier.erase(test_frontier.begin());
      if (s->isWon()) {
        printOutput(s, expanded, output_file);
        return s;
      }
      s->expand();
      expanded++;
      //cout << expanded << endl;
      gameState **children = s->getChildren();
      //cout << "expanded node:" << endl;
      //s->printState();
      //cout << endl;
      //cout << "possible children:" << endl;
      for (int i = 0; i < 5; i++) {
        if (children[i] == NULL)
          continue;
        else {
          //children[i]->printState();
          //cout << "explored count: " << explored.count(children[i]->getStateKey()) << " frontierMap count: " << frontierMap.count(children[i]->getStateKey()) << endl;
          if (explored.count(children[i]->getStateKey()) == 0 && frontierMap.count(children[i]->getStateKey()) == 0) {
            frontier.push(children[i]);
            //test_frontier.push_back(children[i]);
            frontierMap.insert(pair<string, bool>(children[i]->getStateKey(), true));
          }
        }
      }
    }
  }
  return NULL;
}

gameState * dfsSearch(struct state init, struct state goal, char * output_file) {
  cout << "Performing DFS..." << endl;
  gameState * s = new gameState(init, goal);

  //initialize the explored map as empty
  map<string, bool> explored;
  map<string, bool> frontierMap;
  
  //initialize the frontier with the initial state
  stack<gameState *> frontier;
  frontier.push(s);

  int expanded = 0;

  while (true) {
    if (frontier.empty()) {
      cout << "no solution found" << endl;
      return NULL;
    }
    else {
      s = frontier.top();
      explored.insert(pair<string, bool>(s->getStateKey(), true));
      frontier.pop();
      if (s->isWon()) {
        printOutput(s, expanded, output_file);
        return s;
      }
      s->expand();
      expanded++;
      gameState **children = s->getChildren();
      for (int i = 4; i >= 0; i--) {
        if (children[i] == NULL)
          continue;
        else {
          if (explored.find(children[i]->getStateKey()) == explored.end() && frontierMap.find(children[i]->getStateKey()) == frontierMap.end()) {
            frontier.push(children[i]);
            frontierMap.insert(pair<string, bool>(children[i]->getStateKey(), true));
          }
        }
      }
    }
  }
  return NULL;
}

gameState * iddfsSearch(struct state init, struct state goal, char * output_file) {
  cout << "Performing IDDFS..." << endl;
  gameState * i = new gameState(init, goal);

  int expanded = 0;
  for (int depth = 0; depth < INT_MAX; depth++) {
    //initialize the explored map as empty
    map<string, bool> explored;
    map<string, bool> frontierMap;
    
    //initialize the frontier with the initial state
    //vector<gameState *> test_frontier;
    stack<gameState *> frontier;
    frontier.push(i);
    //test_frontier.push_back(i);

    gameState * s = new gameState(init, goal);

    while (true) {
      if (frontier.empty()) {
        break;
      }
      else {
        s = frontier.top();
        explored.insert(pair<string, bool>(s->getStateKey(), true));
        frontier.pop();
        // cout << "frontier:" << endl;
        // for (int i = 0; i < test_frontier.size(); i++) {
        //   test_frontier[i]->printState();
        // }
        // cout << endl;
        // test_frontier.pop_back();
        if (s->isWon()) {
          //cout << s->getDepth() << endl;
          printOutput(s, expanded, output_file);
          return s;
        }
        if (s->getDepth() >= depth) {
          bool remove = true;
          while (remove == true) {
            frontierMap.erase(s->getStateKey());
            explored.erase(s->getStateKey());
            gameState * p = s->getParent();
            gameState ** c = p->getChildren();
            for (int i = 0; i < 5; i++) {
              if (c[i] == NULL)
                continue;
              if (!(explored.find(c[i]->getStateKey()) == explored.end() && frontierMap.find(c[i]->getStateKey()) == frontierMap.end())) {
                remove = false;
              }
            }
            s = p;
          }
          continue;
        }
        s->expand();
        expanded++;
        gameState **children = s->getChildren();
        // cout << "expanded node:" << endl;
        // s->printState();
        // cout << endl;
        // cout << "possible children:" << endl;
        for (int i = 4; i >= 0; i--) {
          if (children[i] == NULL)
            continue;
          else {
            // children[i]->printState();
            if (explored.find(children[i]->getStateKey()) == explored.end() && frontierMap.find(children[i]->getStateKey()) == frontierMap.end()) {
              frontier.push(children[i]);
              // test_frontier.push_back(children[i]);
              frontierMap.insert(pair<string, bool>(children[i]->getStateKey(), true));
            }
          }
        }
      }
    }
  }
  return NULL;
}

gameState * astarSearch(struct state init, struct state goal, char * output_file) {
  cout << "Performing A*..." << endl;

  int expanded = 0;

  //generate the root node
  gameState * s = new gameState(init, goal);
  // bool goal_side = false; // false means the goal is to get chickens on the left
  // if (goal.leftChickens == 0)
  // {
  //   goal_side = true; // the animals should finish on the right
  // }

  //initialize the explored map as empty
  map<string, bool> explored;
  map<string, bool> frontierMap;
  
  //initialize the frontier with the initial state
  priority_queue<gameState *> frontier;
  frontier.push(s);

  while (true) {
    if (frontier.empty()) {
      cout << "no solution found" << endl;
      return NULL;
    }
    else {
      s = frontier.top();
      explored.insert(pair<string, bool>(s->getStateKey(), true));
      frontier.pop();
      if (s->isWon()) {
        printOutput(s, expanded, output_file);
        return s;
      }
      s->expand();
      expanded++;
      gameState **children = s->getChildren();
      for (int i = 0; i < 5; i++) {
        if (children[i] == NULL)
          continue;
        else {
          if (explored.find(children[i]->getStateKey()) == explored.end() && frontierMap.find(children[i]->getStateKey()) == frontierMap.end()) {
            frontier.push(children[i]);
            frontierMap.insert(pair<string, bool>(children[i]->getStateKey(), true));
          }
        }
      }
    }
  }
  return NULL;
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
      s.boat = stoi(n) == 0;
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
