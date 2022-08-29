# Wolves-and-Chickens
The classic Wolves and Chickens puzzle solved with search algorithms in C++

## Introduction
The Wolves and Chickens game is pretty simple: move all the animal from an initial state to a goal state (traditionally 3 of each animal on the left side of a river to start and move all of them to the right side to end). The rules go as follows:
- you have a boat that can move 2 animals at a time across the river
- the boat must have at least 1 animal on it to move across the river
- at no point can there be more wolves than chickens on one side at a time (or else lunch time!)

Try out the game here to familiarize yourself with how it works: https://scratch.mit.edu/projects/175906738/

The purpose of this program is to use Tree Search Algorithms (3 uninformed and 1 informed) to solve the puzzle, finding a solution and computing the algorithms nodes expanded while creating the search tree to find the solution.

## What I Learned

### Tree Search Algorithms
- Depth First Search (DFS)
- Iterative Deepening Depth First Search (IDDFS)
- Breadth First Search (BFS)
- A-Star Search (A*)

## How to Use
### Compile

```make```

### Arguments & Running
Provide the 4 arguments: initial state of the game file, goal state file, mode (algorithm), and output file. 
The initial and goal states should be formatted as follows:

```
3,3,1
0,0,0
```

where the first row is the left side of the river, the second row the right. The columns specify the number of wolves, chickens, and presence or absence of a boat.

The options for algorithm are the following: bfs, dfs, iddfs, astar.

```
./main init.txt goal.txt dfs output.txt
```

### Output
The output file will illustrate each step taken to win the Wolves and Chickens game, as well as the total nodes expanded in the search algorithm and the path length of said solution.


## Write-Up
Please read the write up that more closely explains and observes the behaviors of the program and algorithms: https://docs.google.com/document/d/1FQAtYnc9OZ8qhNgaYtIe_iwV5tHeUTEIc9UMV-yzzTU/edit?usp=sharing
