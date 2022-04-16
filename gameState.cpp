#include "gameState.h"

gameState::gameState() {
    // default init state is all on the left with the boat
    game.boat = false;
    game.leftChickens = 3;
    game.rightChickens = 0;
    game.leftWolves = 3;
    game.rightWolves = 0;
    goal.boat = true;
    goal.leftChickens = 0;
    goal.rightChickens = 3;
    goal.leftWolves = 0;
    goal.rightWolves = 3;
    parent = NULL;
    children = new gameState * [5];
}

gameState::gameState(struct state s, struct state g) {
    game.boat = s.boat;
    game.leftChickens = s.leftChickens;
    game.rightChickens = s.rightChickens;
    game.leftWolves = s.leftWolves;
    game.rightWolves = s.rightWolves;
    goal.boat = g.boat;
    goal.leftChickens = g.leftChickens;
    goal.rightChickens = g.rightChickens;
    goal.leftWolves = g.leftWolves;
    goal.rightWolves = g.rightWolves;
    parent = NULL;
    depth = 0;
    children = new gameState * [5];
}

gameState::gameState(struct state s, gameState * gs) {
    game.boat = s.boat;
    game.leftChickens = s.leftChickens;
    game.rightChickens = s.rightChickens;
    game.leftWolves = s.leftWolves;
    game.rightWolves = s.rightWolves;
    goal = gs->getGoal();
    parent = gs;
    depth = gs->getDepth()+1;
    children = new gameState * [5];
}

gameState * gameState::expand() {
    gameState * gs;
    children[0] = oneChicken();
    children[1] = twoChickens();
    children[2] = oneWolf();
    children[3] = oneEach();
    children[4] = twoWolves();
    return this;
}

// checks how many more moves the game would take if wolves did not have to be <= chickens
int heuristic(gameState * s)
{
  // if (goal_side) // goal is on the right
  // {
  //   return (s->getState().leftChickens + s->getState().leftWolves) / 2;
  // }
  // else // goal is on the left
  // {
  //   return (s->getState().rightChickens + s->getState().rightWolves) / 2;
  // }
  int h = 0;
  struct state state = s->getState();
  int leftChickens = state.leftChickens;
  int leftWolves = state.leftWolves;
  h = abs(s->getGoal().leftChickens - leftChickens) + abs(s->getGoal().leftWolves - leftWolves);
  if (h==2)
    return 1;
  else
    return h;
}

bool gameState::operator<(gameState * s1)
{
    return (s1->getDepth() + heuristic(s1)) > (this->getDepth() + heuristic(this));
}

bool gameState::isWon() {
    return game.boat == goal.boat && game.leftChickens == goal.leftChickens && game.rightChickens == goal.rightChickens && game.leftWolves == goal.leftWolves && game.rightWolves == goal.rightWolves;
}

bool gameState::isLost() {
    return ((game.leftWolves > game.leftChickens) && (game.leftChickens > 0)) || ((game.rightChickens > 0) && (game.rightWolves > game.rightChickens));
}

gameState * gameState::oneChicken() {
    struct state next;
    gameState * s;
    if (!game.boat) {
        if (game.leftChickens > 0) {
            next.leftChickens = game.leftChickens - 1;
            next.rightChickens = game.rightChickens + 1;
            next.boat = !game.boat;
            next.leftWolves = game.leftWolves;
            next.rightWolves = game.rightWolves;
            s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
    else {
        if (game.rightChickens > 0) {
            next.rightChickens = game.rightChickens - 1;
            next.leftChickens = game.leftChickens + 1;
            next.boat = !game.boat;
            next.leftWolves = game.leftWolves;
            next.rightWolves = game.rightWolves;
            s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
}
gameState * gameState::twoChickens() {
    struct state next;
    gameState * s;
    if (!game.boat) {
        if (game.leftChickens > 1) {
            next.leftChickens = game.leftChickens - 2;
            next.rightChickens = game.rightChickens + 2;
            next.boat = !game.boat;
            next.leftWolves = game.leftWolves;
            next.rightWolves = game.rightWolves;
            s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
    else {
        if (game.rightChickens > 1) {
            next.rightChickens = game.rightChickens - 2;
            next.leftChickens = game.leftChickens + 2;
            next.boat = !game.boat;
            next.leftWolves = game.leftWolves;
            next.rightWolves = game.rightWolves;
            s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
}
gameState * gameState::oneWolf() {
    struct state next;
    if (!game.boat) {
        if (game.leftWolves > 0) {
            next.leftWolves = game.leftWolves - 1;
            next.rightWolves = game.rightWolves + 1;
            next.boat = !game.boat;
            next.rightChickens = game.rightChickens;
            next.leftChickens = game.leftChickens;
            gameState * s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
    else {
        if (game.rightWolves > 0) {
            next.rightWolves = game.rightWolves - 1;
            next.leftWolves = game.leftWolves + 1;
            next.boat = !game.boat;
            next.rightChickens = game.rightChickens;
            next.leftChickens = game.leftChickens;
            gameState * s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
}
gameState * gameState::oneEach() {
    struct state next;
    gameState * s;
    if (!game.boat) {
        if (game.leftWolves > 0 && game.leftChickens > 0) {
            next.leftWolves = game.leftWolves - 1;
            next.leftChickens = game.leftChickens - 1;
            next.rightWolves = game.rightWolves + 1;
            next.rightChickens = game.rightChickens + 1;
            next.boat = !game.boat;
            s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
    else {
        if (game.rightWolves > 0 && game.rightChickens > 0) {
            next.rightWolves = game.rightWolves - 1;
            next.rightChickens = game.rightChickens - 1;
            next.leftWolves = game.leftWolves + 1;
            next.leftChickens = game.leftChickens + 1;
            next.boat = !game.boat;
            s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
}

gameState * gameState::twoWolves() {
    struct state next;
    gameState * s;
    if (!game.boat) {
        if (game.leftWolves > 1) {
            next.leftWolves = game.leftWolves - 2;
            next.rightWolves = game.rightWolves + 2;
            next.boat = !game.boat;
            next.rightChickens = game.rightChickens;
            next.leftChickens = game.leftChickens;
            s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
    else {
        if (game.rightWolves > 1) {
            next.rightWolves = game.rightWolves - 2;
            next.leftWolves = game.leftWolves + 2;
            next.boat = !game.boat;
            next.rightChickens = game.rightChickens;
            next.leftChickens = game.leftChickens;
            s = new gameState(next, this);
            if (s->isLost())
                return NULL;
            else
                return s;
        }
        else return NULL;
    }
}

struct state gameState::getState() {
    return game;
}

struct state gameState::getGoal() {
    return goal;
}

gameState ** gameState::getChildren() {
    return children;
}

gameState * gameState::getParent() {
    return parent;
}

int gameState::getDepth() {
    return depth;
}

string gameState::getStateKey() {
    string s = "";
    s = s.append(to_string(game.leftChickens));
    s = s.append(to_string(game.leftWolves));
    s = s.append(to_string(game.boat == false));
    s = s.append(to_string(game.rightChickens));
    s = s.append(to_string(game.rightWolves));
    s = s.append(to_string(game.boat == true));
    return s;
}

void gameState::printState() {
    cout << "---------------------------------\nLeft Bank: \n\tChickens: " << game.leftChickens << "\n\tWolves: " << game.leftWolves << "\n\nRight Bank: \n\tChickens: " << game.rightChickens << "\n\tWolves: " << game.rightWolves << "\n";
}
