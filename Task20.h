//
// Created by marci_000 on 20.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK20_H
#define ADVENTOFCODE2020_TASK20_H

#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"

using image_id = int;
using rotate_image_index = int;
using rotate_image_is_org = bool;
using edge = std::string;
using row = std::string;
using img_data = std::vector<row>;

struct nearby_img_t {
  image_id id;
  edge eg;
  rotate_image_index rot_index;
};
inline bool operator==(const nearby_img_t &lhs, const nearby_img_t &rhs) {
  return lhs.id == rhs.id && lhs.eg == rhs.eg && lhs.rot_index == rhs.rot_index;
}
inline bool operator<(const nearby_img_t &lhs, const nearby_img_t &rhs) {
  return std::make_tuple(lhs.id, lhs.eg, lhs.rot_index) < std::make_tuple(rhs.id, rhs.eg, rhs.rot_index);
}

namespace std {
template<>
struct hash<nearby_img_t> {
  std::size_t operator()(nearby_img_t const &s) const noexcept {
    std::size_t h1 = s.id;
    std::size_t h3 = s.rot_index;
    std::string ss = std::to_string(h1) + s.eg + std::to_string(h3);
    return std::hash<std::string>{}(ss); // or use boost::hash_combine
  }
};
}

void print_image(int id, const img_data &data);

class Task20 {

  struct image {
    image_id id;
    std::vector<img_data> rotated_flipped_images; // rotated, flipped
    std::vector<std::vector<edge>> images_edges; // images_edges[k] are edges for rotated_flipped_images[k]
    std::set<nearby_img_t> nearby_imgs;
  };
  std::unordered_map<int, image> images;
  std::unordered_map<edge, std::unordered_set<std::tuple<image_id, rotate_image_index, rotate_image_is_org>>>
      classified_imgs_map;

  void flip_horizontal(img_data &data);
  img_data flip_horizontal_ex(const img_data &data) {
    img_data d = data;
    flip_horizontal(d);
    return d;
  }

  void flip_vertical(img_data &data);
  img_data flip_vertical_ex(const img_data &data) {
    img_data d = data;
    flip_vertical(d);
    return d;
  }

  void rotateMatrix(img_data &image);
  img_data rotateMatrix_ex(const img_data &image) {
    img_data d = image;
    rotateMatrix(d);
    return d;
  }

  img_data rotateImageAndFlip(const img_data &data, int rotateCount, bool verticalFlip) {
    img_data d = data;

    for (int n = 0; n < rotateCount; ++n) {
      rotateMatrix(d);
    }
    if (verticalFlip) {
      flip_vertical(d);
    } else
      flip_horizontal(d);
    return d;
  }

  img_data rotateImage(const img_data &data, int rotateCount) {
    img_data d = data;

    for (int n = 0; n < rotateCount; ++n) {
      rotateMatrix(d);
    }

    return d;
  }

  void classify_images();

  bool example_data;
 public:
  Task20(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK20_H
