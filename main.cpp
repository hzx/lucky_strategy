#include <iostream>
#include <cstdlib>
#include <vector>


struct Stats {
  bool changeStrategy = false;
  int win = 0;
  int lose = 0;
};


int cutWrongChoice(int car, int choice) {
  if (car == choice) {
    int cutChoice = std::rand() % 2;

    // make shift related to car
    switch (car) {
      case 0:
        ++cutChoice;
        break;
      case 1:
        if (cutChoice == car) ++cutChoice;
        break;
      case 2: // do nothing
        break;
    }

    return cutChoice;
  }

  // choose one free of the three cells
  std::vector<int> busy = {0, 0, 0};

  // set busy with car
  busy[car] = 1;
  busy[choice] = 1;

  for (size_t i = 0; i < busy.size(); ++i) {
    if (busy[i] == 0) return i;
  }
}


void playGame(Stats& stats) {
  // choose car
  int car = std::rand() % 3;

  // make choice
  int choice = std::rand() % 3;

  // cut wrong choice
  int cutted = cutWrongChoice(car, choice);

  // apply strategy
  std::vector<int> cells = {0, 0, 0};
  cells[cutted] = 1;
  cells[choice] = 1;

  int newChoice = choice;

  if (stats.changeStrategy) {
    // choose empty cell
    for (size_t i = 0; i < cells.size(); ++i) {
      if (cells[i] == 0) {
        newChoice = i;
        break;
      }
    }
  }

  // finish
  if (newChoice == car) {
    ++stats.win;
  } else {
    ++stats.lose;
  }
}


int main(int argc, const char *argv[]) {
  Stats changeStats;
  changeStats.changeStrategy = true;

  Stats nochangeStats;
  nochangeStats.changeStrategy = false;

  for (size_t i = 0; i < 1000000; ++i) {
    playGame(changeStats);
    playGame(nochangeStats);
  }

  std::cout << "changeStats, win: " << changeStats.win << ", lose: " << changeStats.lose << std::endl;
  std::cout << "nochangeStats, win: " << nochangeStats.win << ", lose: " << nochangeStats.lose << std::endl;

  return 0;
}
