#include <iostream>
#include <cstdlib>
#include <vector>


struct Stats {
  bool changeStrategy = false;
  size_t win = 0;
  size_t lose = 0;
};


size_t cutWrongChoice(size_t car, size_t choice) {
  std::vector<size_t> cells = {0, 0, 0};
  cells[car] = 1;
  cells[choice] = 1;

  std::vector<size_t> freeIndexes;
  for (size_t i = 0; i < cells.size(); ++i) {
    if (cells[i] == 0) {
      freeIndexes.push_back(i);
    }
  }

  size_t cutted = std::rand() % freeIndexes.size();
  return freeIndexes[cutted];
}


size_t makeNewChoice(size_t choice, size_t cutted) {
  std::vector<size_t> cells = {0, 0, 0};
  cells[cutted] = 1;
  cells[choice] = 1;

  std::vector<size_t> freeIndexes;
  for (size_t i = 0; i < cells.size(); ++i) {
    if (cells[i] == 0) {
      freeIndexes.push_back(i);
    }
  }

  size_t newIndex = std::rand() % freeIndexes.size();
  return freeIndexes[newIndex];
}


void playGame(Stats& stats) {
  // choose car
  size_t car = std::rand() % 3;

  // make choice
  size_t choice = std::rand() % 3;

  // cut wrong choice
  size_t cutted = cutWrongChoice(car, choice);

  // apply strategy
  size_t newChoice = choice;
  if (stats.changeStrategy) {
    newChoice = makeNewChoice(choice, cutted);
  }

  // finish
  if (newChoice == car) {
    ++stats.win;
  } else {
    ++stats.lose;
  }
}


int main(int argc, const char *argv[]) {
  size_t const GAMES_COUNT = 100;

  Stats change;
  change.changeStrategy = true;

  Stats nochange;
  nochange.changeStrategy = false;

  for (size_t i = 0; i < GAMES_COUNT; ++i) {
    playGame(change);
  }

  for (size_t i = 0; i < GAMES_COUNT; ++i) {
    playGame(nochange);
  }

  std::cout << "change, win: " << change.win << ", lose: " << change.lose << std::endl;
  std::cout << "nochange, win: " << nochange.win << ", lose: " << nochange.lose << std::endl;

  return 0;
}
