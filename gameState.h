#include <string>
#include <iostream>
#include "state.h"

#ifndef GAMESTATE
#define GAMESTATE

using namespace std;

class gameState {
    public:
        int depth;
        gameState();
        gameState(struct state, struct state);
        gameState(struct state, gameState *);

        gameState * expand();

        bool isWon(); //current state is the goal state
        bool isLost(); //current state is a losing state

        gameState * oneChicken(); //one chicken on the boat
        gameState * twoChickens(); //two chickens on the boat
        gameState * oneWolf(); //one wolf on the boat
        gameState * oneEach(); //one chicken and one wolf on the boat
        gameState * twoWolves(); //two wolves on the boat

        bool operator()(const gameState *, const gameState *) const;
        int heuristic(const gameState *) const;

        struct state getState(); //public accessor function of the state
        gameState ** getChildren();
        gameState * getParent();
        int getDepth();
        struct state getGoal();
        struct state getStateConst() const;
        struct state getGoalConst() const;
        int getDepthConst() const;


        string getStateKey(); //accessor for unique string representation of current state (331001)
    
        void printState();

    private:
        struct state game;
        struct state goal;
        gameState * parent;
        gameState ** children;
};

#endif