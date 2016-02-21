#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>


struct Player {
  std::string name;
  bool alwaysChange = false;
  size_t win = 0;
  size_t lose = 0;

  void print() {
    std::cout << '[' << name << "] alwaysChange: " << alwaysChange <<
      ", win: " << win << ", lose: " << lose << std::endl;
  }
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


void playGame(Player& player) {
  // choose car
  size_t car = std::rand() % 3;

  // make choice
  size_t choice = std::rand() % 3;

  // cut wrong choice
  size_t cutted = cutWrongChoice(car, choice);

  // apply strategy
  size_t newChoice = player.alwaysChange ?
    makeNewChoice(choice, cutted) :  choice;

  // finish
  if (newChoice == car) {
    ++player.win;
  } else {
    ++player.lose;
  }
}


int main(int argc, const char *argv[]) {
  size_t const GAMES_COUNT = 100;

  Player brave {
    name: "brave",
    alwaysChange: true,
  };

  Player coward {
    name: "coward",
    alwaysChange: false,
  };

  for (size_t i = 0; i < GAMES_COUNT; ++i) {
    playGame(brave);
  }

  for (size_t i = 0; i < GAMES_COUNT; ++i) {
    playGame(coward);
  }

  brave.print();
  coward.print();

  return 0;
}
