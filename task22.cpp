//
// Created by marci_000 on 26.12.2020.
//

#include "task22.h"

#include <fstream>
#include <iostream>
#include <string>
#include "utils.h"

Task22::Task22(bool example) {
  example_data = example;

  std::ifstream ifs(example ? "../data/data22_example.txt" : std::string("../") + get_relative_data_path() + "data/data22_task.txt");
  std::string line;
  while (std::getline(ifs, line)) {
    if (line == "Player 1:")
      continue;
    if (line.empty())
      break;
    player1_org.push_back(std::stoi(line));
  }

  while (std::getline(ifs, line)) {
    if (line == "Player 2:")
      continue;
    if (line.empty())
      break;
    player2_org.push_back(std::stoi(line));
  }
}

void Task22::Solve1() {
  Timer opt_timer;

  auto player1 = player1_org;
  auto player2 = player2_org;

  int rounds = 0;
  while (true) {
    if (player1.empty())
      break;
    if (player2.empty())
      break;

    int card_player1 = player1.front();
    player1.pop_front();
    int card_player2 = player2.front();
    player2.pop_front();

    if (card_player1 > card_player2) {
      player1.push_back(card_player1);
      player1.push_back(card_player2);
    } else {
      player2.push_back(card_player2);
      player2.push_back(card_player1);
    }
    rounds++;
  }

  std::deque<int> &winners_deck = player1.empty() ? player2 : player1;

  int result = 0;
  while (!winners_deck.empty()) {
    result += winners_deck.size() * winners_deck.front();
    winners_deck.pop_front();
  }

  verify_result(result, example_data ? 306 : get_data_result<uint64_t>(22, 1));
  std::cout << " part1: result = " << result << std::endl;
}

void Task22::recurive_combat(std::deque<int> &player1, std::deque<int> &player2, bool &player1wins) {
  std::set<std::deque<int>> previous_rounds;
  int rounds = 0;
  while (true) {
    if (player1.empty())
      break;
    if (player2.empty())
      break;

    player1wins = false;

    int card_player1 = -1;
    int card_player2 = -1;

    if (previous_rounds.contains(player1) || previous_rounds.contains(player2)) {
      player1wins = true;
      return;
    } else {
      previous_rounds.insert(player1);
      previous_rounds.insert(player2);

      card_player1 = player1.front();
      player1.pop_front();
      card_player2 = player2.front();
      player2.pop_front();

      if (card_player1 <= player1.size() && card_player2 <= player2.size()) {
        std::deque<int> player1_subgame(player1.begin(), player1.begin() + card_player1);
        std::deque<int> player2_subgame(player2.begin(), player2.begin() + card_player2);
        recurive_combat(player1_subgame, player2_subgame, player1wins);
      } else {
        player1wins = card_player1 > card_player2;
      }
    }

    if (card_player1 == -1 || card_player2 == -1)
      throw "WTF!";

    if (player1wins) {
      player1.push_back(card_player1);
      player1.push_back(card_player2);
    } else {
      player2.push_back(card_player2);
      player2.push_back(card_player1);
    }

    rounds++;
  }
}

void Task22::Solve2() {
  Timer opt_timer;
  auto player1 = player1_org;
  auto player2 = player2_org;

  bool player1wins = false;
  recurive_combat(player1, player2, player1wins);

  std::deque<int> &winners_deck = player1.empty() ? player2 : player1;

  int result = 0;
  while (!winners_deck.empty()) {
    result += winners_deck.size() * winners_deck.front();
    winners_deck.pop_front();
  }

  verify_result(result, example_data ? 291 : get_data_result<uint64_t>(22, 2));
  std::cout << " part2: result = " << result << std::endl;
}
