/**
 * C++ class for a game of the Tower of Hanoi puzzle.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "Game.h"
#include "Stack.h"
#include "uiuc/Cube.h"
#include "uiuc/HSLAPixel.h"

#include <iostream>
using std::cout;
using std::endl;

// Solves the Tower of Hanoi puzzle.

/* THIS IS MY CODE BELOW */
// (Feel free to call "helper functions" to help you solve the puzzle.)
int Game::getSmallestCubeIndex() {
  int i = 0;
  for (; i < 3; i++) {
    if (!stacks_[i].size()) continue;
    if (stacks_[i].peekTop().getLength() == 1) break;
  }
  return i;
}

void Game::moveSmallestCube() {
  int smallIndex = getSmallestCubeIndex();
  Cube cube = stacks_[smallIndex].removeTop();
  stacks_[(smallIndex + 1) % 3].push_back(cube);
}

void Game::moveCube() {
  int smallIndex = getSmallestCubeIndex();
  
  int j = (smallIndex + 1) % 3;
  int jLength = 10;
  if (stacks_[j].size()) jLength = stacks_[j].peekTop().getLength();

  int k = (smallIndex + 2) % 3;
  int kLength = 10;
  if (stacks_[k].size()) kLength = stacks_[k].peekTop().getLength();

  if (jLength > kLength) {
    Cube cube = stacks_[k].removeTop();
    stacks_[j].push_back(cube);
  } else {
    Cube cube = stacks_[j].removeTop();
    stacks_[k].push_back(cube);
  }
}

void Game::solve() {
  // @TODO -- Finish solving the game!
  int i = 1;
  while (stacks_[2].size() != 4) {
    cout << "Move: " << i << endl;
    if (i % 2 != 0) moveSmallestCube();
    else moveCube();
    i++;
    // Prints out the state of the game:
    cout << *this << endl;
  }
}

/* END MY CODE */

// Default constructor to create the initial state:
Game::Game() {
  // Create the three empty stacks:
  for (int i = 0; i < 3; i++) {
    Stack stackOfCubes;
    stacks_.push_back( stackOfCubes );
  }

  // Create the four cubes, placing each on the [0]th stack:
  Cube blue(4, uiuc::HSLAPixel::BLUE);
  stacks_[0].push_back(blue);

  Cube orange(3, uiuc::HSLAPixel::ORANGE);
  stacks_[0].push_back(orange);

  Cube purple(2, uiuc::HSLAPixel::PURPLE);
  stacks_[0].push_back(purple);

  Cube yellow(1, uiuc::HSLAPixel::YELLOW);
  stacks_[0].push_back(yellow);
}

std::ostream& operator<<(std::ostream & os, const Game & game) {
  for (unsigned i = 0; i < game.stacks_.size(); i++) {
    os << "Stack[" << i << "]: " << game.stacks_[i];
  }
  return os;
}
