//
// Created by marci_000 on 05.01.2021.
//

#include "task25.h"
#include <fstream>
#include <string>
#include <iostream>
#include "utils.h"

Task25::Task25(bool example) {
  example_data = example;
  std::ifstream ifs(example ?
      std::string("../data/data25_example.txt") :
      std::string("../") + get_relative_data_path() + "data/data25_task.txt");
  std::string line;
  if (std::getline(ifs, line))
    card_pubkey = std::stoull(line);
  if (std::getline(ifs, line))
    door_pubkey = std::stoull(line);
}

void Task25::Solve1() {
  Timer opt_timer;
  uint64_t subject = 7;
  uint64_t div_num = 20201227;

  int card_loop_size;
  int door_loop_size;

  uint64_t val = 1;
  for (card_loop_size = 0; ; ++card_loop_size) {
    val *= subject;
    val %= div_num;
    if (val == card_pubkey) {
      card_loop_size++;
      break;
    }
  }

  val = 1;
  for (door_loop_size = 0; ; ++door_loop_size) {
    val *= subject;
    val %= div_num;
    if (val == door_pubkey) {
      door_loop_size++;
      break;
    }
  }

  //end

  uint64_t enc_key_1 = 1;
  for (int i = 0; i < card_loop_size; ++i) {
    enc_key_1 *= door_pubkey;
    enc_key_1 %= div_num;
  }
  uint64_t enc_key_2 = 1;
  for (int i = 0; i < door_loop_size; ++i) {
    enc_key_2 *= card_pubkey;
    enc_key_2 %= div_num;
  }

  verify_result(enc_key_1, enc_key_2);
  uint64_t enc_key = enc_key_1;
  verify_result(enc_key, example_data ? 14897079 : get_data_result<uint64_t>(25, 1));
  std::cout << " part1: encryption key = " << enc_key << std::endl;
}

void Task25::Solve2() {
  // none
}
