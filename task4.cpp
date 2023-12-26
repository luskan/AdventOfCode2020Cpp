//
// Created by marcin on 06.12.2020.
//

#include "task4.h"
#include <regex>
#include <fstream>
#include <iostream>
#include "utils.h"

Task4::Task4(bool example) {
  example_data = example;
  std::ifstream ifs(example_data ? "../data/data4_example.txt" : std::string("../") + get_relative_data_path() + "data/data4_task.txt");
  std::string line;

  std::regex regLine{R"((\w+):([#\w\d]+))",
      std::regex_constants::ECMAScript | std::regex_constants::icase};

  PassportData pd;
  while (std::getline(ifs, line)) {
    if (line.size() == 0) {
      allPassports.push_back(pd);
      pd.clear();
    }

    std::sregex_iterator reg_begin(line.begin(), line.end(), regLine);
    std::sregex_iterator reg_end = std::sregex_iterator();
    for (auto ri = reg_begin; ri != reg_end; ++ri) {
      std::smatch m = *ri;
      if (m.size() != 3)
        throw "Wrong number of fields parsed!";
      pd[m[1]] = m[2];
    }
  }
  allPassports.push_back(pd);
}

int Task4::countCorrect(bool validate) {
  int correct = 0;
  for (size_t i = 0; i != allPassports.size(); ++i) {
    if (allPassports[i].size() == 8) {
      if (validate && !isValid(allPassports[i]))
        continue;
      correct++;
      continue;
    }
    if (allPassports[i].size() == 7 && !allPassports[i].contains("cid")) {
      if (validate && !isValid(allPassports[i]))
        continue;
      correct++;
      continue;
    }
  }
  return correct;
}

void Task4::Solve1() {
  Timer opt_timer;
  auto count = countCorrect(false);
  verify_result(count, example_data ? 2 : get_data_result<int>(4, 1));
  std::cout << " part1: valid passports = " << count << std::endl;
}

void Task4::Solve2() {
  Timer opt_timer;
  auto count = countCorrect(true);
  // In part2 example data, there was no correct answer to sample data. Only few valid/invalid passports were presentd.
  verify_result(count, example_data ? 2 : get_data_result<int>(4, 2));
  std::cout << " part2: valid passports = " << count << std::endl;
}

bool Task4::isValid(std::map<std::string, std::string> &map) {
  int tmp = std::stoi(map["byr"]);
  if (tmp < 1920 || tmp > 2002) // byr (Birth Year) - four digits; at least 1920 and at most 2002.
    return false;

  tmp = std::stoi(map["iyr"]);
  if (tmp < 2010 || tmp > 2020) // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
    return false;

  tmp = std::stoi(map["eyr"]);
  if (tmp < 2010 || tmp > 2030) // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
    return false;

  //hgt (Height) - a number followed by either cm or in:
  //  If cm, the number must be at least 150 and at most 193.
  //  If in, the number must be at least 59 and at most 76.
  std::smatch sm;
  if (std::regex_match(map["hgt"], sm, std::regex(R"((\d+)(cm|in))"))) {
    tmp = std::stoi(sm[1]);
    if (sm[2] == "cm")
      if (tmp < 150 || tmp > 193)
        return false;
    if (sm[2] == "in")
      if (tmp < 59 || tmp > 76)
        return false;
  } else {
    return false;
  }

  // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
  if (!std::regex_match(map["hcl"], std::regex(R"(#[0-9a-f]{6})")))
    return false;

  // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
  if (!std::regex_match(map["ecl"], std::regex(R"((amb|blu|brn|gry|grn|hzl|oth))")))
    return false;

  // pid (Passport ID) - a nine-digit number, including leading zeroes.
  if (!std::regex_match(map["pid"], std::regex(R"([0-9]{9})")))
    return false;

  // cid (Country ID) - ignored, missing or not.
  return true;
}
