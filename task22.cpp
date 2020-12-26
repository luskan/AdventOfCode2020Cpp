//
// Created by marci_000 on 26.12.2020.
//

#include "task22.h"

#include <fstream>
#include <iostream>
#include <string>

task22::task22() {
    std::ifstream ifs("../data22.txt");
    std::string line;
    while(std::getline(ifs, line)) {
        if (line == "Player 1:")
            continue;
        if (line.empty())
            break;
        player1_org.push_back(std::stoi(line));
    }

    while(std::getline(ifs, line)) {
        if (line == "Player 2:")
            continue;
        if (line.empty())
            break;
        player2_org.push_back(std::stoi(line));
    }
}

void task22::solve1() {

    auto player1 = player1_org;
    auto player2 = player2_org;

    int rounds = 0;
    while(true) {
        if (player1.empty())
            break;
        if(player2.empty())
            break;

        int card_player1 = player1.front();
        player1.pop_front();
        int card_player2 = player2.front();
        player2.pop_front();

        if (card_player1 > card_player2) {
            player1.push_back(card_player1);
            player1.push_back(card_player2);
        }
        else {
            player2.push_back(card_player2);
            player2.push_back(card_player1);
        }
        rounds++;
    }

    std::deque<int>& winners_deck = player1.empty() ? player2 : player1;

    int result = 0;
    while (!winners_deck.empty()) {
        result += winners_deck.size() * winners_deck.front();
        winners_deck.pop_front();
    }
    std::cout << "Solution1: " << result << std::endl;
}

void task22::recurive_combat(std::deque<int>& player1, std::deque<int>& player2, bool& player1wins) {
    std::set<std::deque<int>> previous_rounds;
    int rounds = 0;
    while(true) {
        if (player1.empty())
            break;
        if(player2.empty())
            break;

        player1wins = false;

        int card_player1 = -1;
        int card_player2 = -1;

        if (previous_rounds.contains(player1) || previous_rounds.contains(player2)) {
            player1wins = true;
            return;
        }
        else {
            previous_rounds.insert(player1);
            previous_rounds.insert(player2);

            card_player1 = player1.front();
            player1.pop_front();
            card_player2 = player2.front();
            player2.pop_front();

            if (card_player1 <= player1.size() && card_player2 <= player2.size()) {
                std::deque<int> player1_subgame(player1.begin(), player1.begin()+card_player1);
                std::deque<int> player2_subgame(player2.begin(), player2.begin()+card_player2);
                recurive_combat(player1_subgame, player2_subgame, player1wins);
            }
            else {
                player1wins = card_player1 > card_player2;
            }
        }

        if (card_player1 == -1 || card_player2 == -1)
            throw "WTF!";

        if (player1wins) {
            player1.push_back(card_player1);
            player1.push_back(card_player2);
        }
        else {
            player2.push_back(card_player2);
            player2.push_back(card_player1);
        }

        rounds++;
    }
}

void task22::solve2() {
    auto player1 = player1_org;
    auto player2 = player2_org;

    bool player1wins = false;
    recurive_combat(player1, player2, player1wins);

    std::deque<int>& winners_deck = player1.empty() ? player2 : player1;

    int result = 0;
    while (!winners_deck.empty()) {
        result += winners_deck.size() * winners_deck.front();
        winners_deck.pop_front();
    }
    std::cout << "Solution2: " << result << std::endl;
}
