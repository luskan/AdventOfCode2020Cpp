//
// Created by marci_000 on 20.12.2020.
//

#include "Task20.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <random>
#include "utils.h"

void print_image(int id, const img_data &data) {
  if (id != -1)
    std::cout << "Tile " << id << ":" << std::endl;
  std::ofstream ofs("../data/data20_out.txt", std::ios::trunc);
  for (auto &row : data) {
    auto count = std::count_if(row.begin(), row.end(), [](auto it) { return it != ' '; });
    if (count == 0)
      break;
    std::cout << row << std::endl;
    ofs << row << std::endl;
  }
}

Task20::Task20(bool example) {
  example_data = example;
  std::ifstream ifs(example ? "../data/data20_example.txt" : std::string("../") + get_relative_data_path() + "data/data20_task.txt");
  std::string line;
  std::regex rg(R"(Tile (\d+):)");

  while (std::getline(ifs, line)) {
    image img;
    if (line.empty())
      continue;
    std::smatch sm;
    if (!std::regex_match(line, sm, rg))
      throw "Invalid format!";

    img.id = std::stoi(sm[1]);

    img_data img_d;
    while (std::getline(ifs, line)) {
      if (line.empty())
        break;
      img_d.push_back(line);
    }

    // Find all possible rotations and flips
    for (int ik = 0; ik < 4; ++ik) {

      // Rotate with no flip/flop
      img.rotated_flipped_images.push_back(rotateImage(img_d, ik));

      // Rotate then flip/flop
      img.rotated_flipped_images.push_back(rotateImageAndFlip(img_d, ik, false));
      img.rotated_flipped_images.push_back(rotateImageAndFlip(img_d, ik, true));
    }

    // Remove duplicates
    std::sort(img.rotated_flipped_images.begin(), img.rotated_flipped_images.end());
    img.rotated_flipped_images.erase(std::unique(img.rotated_flipped_images.begin(), img.rotated_flipped_images.end()),
                                     img.rotated_flipped_images.end());

    // Sanity check
    if (images.contains(img.id))
      throw "Duplicated image?";

    images[img.id] = std::move(img);
  }

  // Do the initiali image border by border classification.
  classify_images();
}

void Task20::classify_images() {

  // For each image rotation, store all its four borders in std::strings with additional prefix
  // indicating whether its is top/right/bottom or left. Then put it in the map with border with prefix
  // as key and value is the data on which border/image/rotation it belongs it. The same four borders are
  // used as entries to the same map but with changed prefixes - this time top (_t) border prefix is changed
  // to bottom (_b) - this way we match this image borders with other borders from different tile images.

  for (auto&[id, im] : images) {
    for (size_t flipped_image_index = 0; flipped_image_index < im.rotated_flipped_images.size();
         ++flipped_image_index) {
      auto &rotated_im = im.rotated_flipped_images[flipped_image_index];

      std::string top, right, bottom, left;

      top = rotated_im[0];
      bottom = rotated_im.back();
      for (auto &line : rotated_im) {
        right += line.back();
        left += *line.begin();
      }

      // All edges.
      std::vector<edge> rot_img_edges;
      rot_img_edges.push_back(top);
      rot_img_edges.push_back(right);
      rot_img_edges.push_back(bottom);
      rot_img_edges.push_back(left);
      im.images_edges.push_back(std::move(rot_img_edges));

      // Insert this image edges as new entries.
      int n = 0;
      for (auto &edg : im.images_edges.back()) {
        std::string sufix;
        if (n == 0)
          sufix = "_t";
        else if (n == 1)
          sufix = "_r";
        else if (n == 2)
          sufix = "_b";
        else if (n == 3)
          sufix = "_l";
        else
          throw "WTF!";
        classified_imgs_map[edg + sufix].insert(
            std::make_tuple(im.id, im.images_edges.size() - 1, true));
        n++;
      }

      // Insert this image edges as matching other entries.
      n = 0;
      for (auto &edg : im.images_edges.back()) {
        std::string sufix;
        if (n == 0)
          sufix = "_b";
        else if (n == 1)
          sufix = "_l";
        else if (n == 2)
          sufix = "_t";
        else if (n == 3)
          sufix = "_r";
        else
          throw "WTF!";
        std::string edge_check = edg + sufix;
        classified_imgs_map[edge_check].insert(std::make_tuple(im.id, im.images_edges.size() - 1, false));
        n++;
      }
    }
  }

  // We have now map of borders with images assigned to them, we now know which image (its transformation)
  // is near any other image. For each image, find its nearby images.
  for (auto&[edge, id_set] : classified_imgs_map) {
    for (auto &id : id_set) {
      int id_1 = std::get<0>(id);
      for (auto id2 : id_set) {
        int id_2 = std::get<0>(id2);
        if (id_1 != id_2) {
          bool is_org_image = std::get<2>(id2);
          if (!is_org_image) {
            auto &ni = images[id_1].nearby_imgs;
            nearby_img_t nearimg{
                id_2, // image id
                edge,   // Edge at which was match
                std::get<1>(id2) // index of rotated image
            };
            ni.insert(nearimg);
          }
        }
      }
    }
  }
}

void Task20::Solve1() {
  Timer opt_timer;

  // We have computed all possibly rotation of each image, then for each image rotation classified their edges to find
  // nearby images. Now we want to find corner images, to do this we find images for each rotations will have at most
  // 2 nearby images.

  // Variable for result.
  uint64_t total = 1;

  // Iterate each image.
  for (auto&[id, im] : images) {

    // Use map to count for each
    using nearby_image_count_for_rotation = int;
    std::unordered_map<rotate_image_index, nearby_image_count_for_rotation> im_index_count;
    for (const auto &rotated_img : im.nearby_imgs) {
      im_index_count[rotated_img.rot_index]++;
    }

    // Now find max count of nearby images for each rotation
    int max_nearbys_for_rotation = 0;
    for (auto&[rot_index, count] : im_index_count) {
      max_nearbys_for_rotation = std::max(max_nearbys_for_rotation, count);
    }
    if (max_nearbys_for_rotation == 2) {
      total *= id;
    }
  }

  verify_result(total, example_data ? 20899048083289ull : get_data_result<uint64_t>(20, 1));
  std::cout << " part1: total = " << total << std::endl;
}

void Task20::Solve2() {
  Timer opt_timer;

  // Here we will reconstruct image, to do this we will start from top left corner (candidates for it are
  // found in Solve1()). Then for each image we will construct nearby images.

  using img_x_t = int;
  using img_y_t = int;
  using top_left_candidate_t = std::tuple<image_id, rotate_image_index, img_x_t, img_y_t>;
  std::vector<top_left_candidate_t> candidated_for_top_left;

  // Final image is a square, find how many tiles are on each side.
  int side_size = sqrt(images.size());

  // This is a side size of tile.
  int img_side_size = images.begin()->second.rotated_flipped_images[0].size();

  // Find candidates for starting top/left tile. Code is similar as in Solve1(). This could be found by edge analyzis.
  for (auto&[id, im] : images) {

    // Use edge classification map to count number of nearby images for each rotation.
    using nearby_image_count_for_rotation = int;
    std::unordered_map<rotate_image_index, nearby_image_count_for_rotation> im_index_count;
    for (const auto &rotated_img : im.nearby_imgs) {
      im_index_count[rotated_img.rot_index]++;
    }

    // Now find max count of nearby images for each rotation
    int max_nearbys_for_rotation = 0;
    for (auto&[rot_index, count] : im_index_count) {
      max_nearbys_for_rotation = std::max(max_nearbys_for_rotation, count);
    }
    if (max_nearbys_for_rotation == 2) {
      for (auto&[rot_index, count] : im_index_count) {
        if (count == 2) {
          const int final_image_pos_x = 0;
          const int final_image_pos_y = 0;
          candidated_for_top_left.push_back(std::make_tuple(id, rot_index, final_image_pos_x, final_image_pos_y));
        }
      }
    }
  }

  // Matrix with image IDs of final assembled image.
  std::vector<std::vector<std::tuple<image_id, rotate_image_index>>> image_matrix;
  image_matrix.resize(side_size);
  for (auto &row : image_matrix) {
    row.resize(side_size);
    std::fill(row.begin(), row.end(), std::make_tuple(-1, -1));
  }

  // Queue will store new images added while traversing whole image.
  std::queue<std::tuple<image_id, rotate_image_index, int, int>> img_queue;
  bool found = false;

  // Start iterating each top/left candidate.
  for (auto&[top_left_img_id, top_left_rot_index, img_pos_x, img_pos_y] : candidated_for_top_left) {
    img_queue.push(std::make_tuple(top_left_img_id, top_left_rot_index, img_pos_x, img_pos_y));

    // When trying new top/left image, we must reset whole image.
    for (auto &row : image_matrix)
      std::fill(row.begin(), row.end(), std::make_tuple(-1, -1));

    bool first_run = true;
    while (!img_queue.empty()) {
      auto[img_id, rot_index, img_row, img_col] = img_queue.front();
      img_queue.pop();

      image &img = images[img_id];

      if (first_run) {
        img_data &img_data_1 = img.rotated_flipped_images[rot_index];
        image_matrix[img_row][img_col] = std::make_tuple(img_id, rot_index);
        first_run = false;
      }

      for (auto &near_img : img.nearby_imgs) {
        for (int edge_img_index = 0; edge_img_index < img.images_edges[rot_index].size(); ++edge_img_index) {
          auto edge_img_border = img.images_edges[rot_index][edge_img_index];
          if (edge_img_index == 0)
            edge_img_border += "_t";
          else if (edge_img_index == 1)
            edge_img_border += "_r";
          else if (edge_img_index == 2)
            edge_img_border += "_b";
          else if (edge_img_index == 3)
            edge_img_border += "_l";
          else
            throw "WTF!";
          if (near_img.eg == edge_img_border) {
            int near_img_row = img_row;
            int near_img_col = img_col;
            if (edge_img_border.ends_with("_r"))
              near_img_col++;
            if (edge_img_border.ends_with("_l"))
              near_img_col--;
            if (edge_img_border.ends_with("_t"))
              near_img_row--;
            if (edge_img_border.ends_with("_b"))
              near_img_row++;

            if (near_img_col < 0 || near_img_col >= side_size)
              continue;
            if (near_img_row < 0 || near_img_row >= side_size)
              continue;

            if (std::get<0>(image_matrix[near_img_row][near_img_col]) != -1)
              continue;

            bool repeated = false;
            for (int ik1 = 0; ik1 < image_matrix.size(); ik1++) {
              for (int ik2 = 0; ik2 < image_matrix[ik1].size(); ik2++) {
                if (std::get<0>(image_matrix[ik1][ik2]) == near_img.id)
                  repeated = true;
              }
            }
            if (repeated) {
              continue;
            }

            img_queue.push({near_img.id, near_img.rot_index, near_img_row, near_img_col});

            image &img = images[near_img.id];
            img_data &img_data_2 = img.rotated_flipped_images[near_img.rot_index];
            image_matrix[near_img_row][near_img_col] = std::make_tuple(near_img.id, near_img.rot_index);
          }
        }
      }
    }

    int total_used_images = 0;
    for (int ik1 = 0; ik1 < image_matrix.size(); ik1++) {
      for (int ik2 = 0; ik2 < image_matrix[ik1].size(); ik2++) {
        if (std::get<0>(image_matrix[ik1][ik2]) != -1)
          total_used_images++;
      }
    }
    if (total_used_images == side_size * side_size) {
      found = true;
      break;
    }
  }

  //
  // Final assembled image.

  const bool add_extra_info = false; // true - enables additional info in final image
  // false - forms final image with no border on tiles

  img_data entire_image;
  entire_image.resize(side_size * (img_side_size + (add_extra_info ? 2 : -2)));
  for (auto &row : entire_image) {
    row.resize((img_side_size + (add_extra_info ? 2 : -2)) * side_size);
    std::fill(row.begin(), row.end(), ' ');
  }

  // Some messy code (bcos it allows for some debug visualizations) to copy images to form big one.
  for (size_t img_row = 0; img_row < image_matrix.size(); img_row++) {
    for (size_t img_col = 0; img_col < image_matrix[img_row].size(); img_col++) {
      image_id id = std::get<0>(image_matrix[img_row][img_col]);
      rotate_image_index rot_index = std::get<1>(image_matrix[img_row][img_col]);

      if (add_extra_info) {
        std::string title = std::to_string(id) + ":" + std::to_string(rot_index);
        std::copy(title.begin(), title.end(),
                  entire_image[img_row * (img_side_size + 1)].begin() + 1 +
                      img_col * (img_side_size + 1));
      }
      img_data &image_data = images[id].rotated_flipped_images[rot_index];
      for (std::size_t i = (add_extra_info ? 0 : 1); i < image_data.size() - (add_extra_info ? 0 : 1); ++i) {
        auto &row = image_data[i];
        std::copy(row.begin() + (add_extra_info ? 0 : 1), row.end() - (add_extra_info ? 0 : 1),
                  entire_image[img_row * (img_side_size + (add_extra_info ? 1 : -2)) + i
                      + (add_extra_info ? 1 : -1)].begin()
                      + (add_extra_info ? 1 : 0) +
                      img_col * (img_side_size + (add_extra_info ? 1 : -2)));
      }
    }
  }

  //
  // Now find the monster!

  const char *monster_pattern[] = {
      "                  # ",
      "#    ##    ##    ###",
      " #  #  #  #  #  #   "
  };

  int actual_monster_pixel_count = 0;
  int monster_image_line_len = strlen(monster_pattern[0]);
  for (size_t m_y = 0; m_y < sizeof(monster_pattern) / sizeof(monster_pattern[0]); ++m_y) {
    const char *sz_line = monster_pattern[m_y];
    for (size_t m_x = 0; m_x < monster_image_line_len; ++m_x) {
      if (monster_pattern[m_y][m_x] == '#')
        actual_monster_pixel_count++;
    }
  }

  // Make rotated/flipped images
  std::vector<img_data> entire_image_rots;
  for (int ik = 0; ik < 4; ++ik) {
    entire_image_rots.push_back(rotateImage(entire_image, ik));
    entire_image_rots.push_back(rotateImageAndFlip(entire_image, ik, false));
    entire_image_rots.push_back(rotateImageAndFlip(entire_image, ik, true));
  }
  // Remove duplicates
  std::sort(entire_image_rots.begin(), entire_image_rots.end());
  entire_image_rots.erase(
      std::unique(entire_image_rots.begin(), entire_image_rots.end()), entire_image_rots.end());

  int total_sea_roughness = 0;
  int total_monsters_found = 0;

  for (int rot = 0; rot < entire_image_rots.size(); ++rot) {
    img_data &entire_image = entire_image_rots[rot];
    total_monsters_found = 0;
    std::unordered_set<std::tuple<int, int>> sea_monster_pixels;

    for (size_t im_y = 0; im_y < entire_image.size(); ++im_y) {
      for (size_t im_x = 0; im_x < entire_image[im_y].size(); ++im_x) {

        bool abort = false;
        int monster_pixel_count = 0;
        std::unordered_set<std::tuple<int, int>> this_part_sea_monster_pixels;
        for (size_t m_y = 0; m_y < sizeof(monster_pattern) / sizeof(monster_pattern[0]) && !abort; ++m_y) {
          for (size_t m_x = 0; m_x < monster_image_line_len && !abort; ++m_x) {

            char monster_c = monster_pattern[m_y][m_x];
            size_t img_m_y = im_y + m_y;
            size_t img_m_x = im_x + m_x;

            if (img_m_y >= entire_image.size()
                || img_m_x >= entire_image[im_y].size()) {
              abort = true;
              break;
            }
            char image_c = entire_image[img_m_y][img_m_x];

            if (image_c == monster_c) {
              monster_pixel_count++;
              this_part_sea_monster_pixels.insert(std::make_tuple(img_m_x, img_m_y));
            }
          }
        }
        if (!abort && monster_pixel_count == actual_monster_pixel_count) {
          sea_monster_pixels.merge(this_part_sea_monster_pixels);
          total_monsters_found++;
        }

      }
    }

    total_sea_roughness = 0;
    for (size_t im_y = 0; im_y < entire_image.size(); ++im_y) {
      for (size_t im_x = 0; im_x < entire_image[im_y].size(); ++im_x) {
        if (entire_image[im_y][im_x] == '#') {
          if (!sea_monster_pixels.contains(std::make_tuple(im_x, im_y))) {
            total_sea_roughness++;
          }
        }
      }
    }

    if (total_monsters_found != 0) {
      break;
      //std::cout << "Solution 2:" << std::endl;
      //std::cout << " " << rot << std::endl;
      //std::cout << "  total_monsters_found: " << total_monsters_found << std::endl;
      //std::cout << "  sea_roughness: " << total_sea_roughness << std::endl;
    }
  }

  //print_image(-1, entire_image);

  verify_result(total_sea_roughness, example_data ? 273 : get_data_result<uint64_t>(20, 2));
  std::cout << " part2: total = " << total_sea_roughness << std::endl;
}

void Task20::flip_horizontal(std::vector<row> &data)  // flips left-right
{
  for (int rr = 0; rr < data[0].size(); rr++) {
    for (int cc = 0; cc < data.size() / 2; cc++) {
      int ccInv = data.size() - 1 - cc;
      std::swap<char>(data[rr][cc], data[rr][ccInv]);
    }
  }
}

void Task20::flip_vertical(std::vector<row> &data)  // flips: bottom-up
{
  for (int cc = 0; cc < data[0].size(); cc++) {
    for (int rr = 0; rr < data.size() / 2; rr++) {
      int rrInv = data.size() - 1 - rr;
      std::swap<char>(data[rr][cc], data[rrInv][cc]);
    }
  }
}

void Task20::rotateMatrix(std::vector<row> &image) {
  if (image.size() != image[0].size())
    throw "Square image only!";
  int image_size = image.size();

  // Consider all squares one by one
  for (int x = 0; x < image_size / 2; x++) {
    // Consider elements in group
    // of 4 in current square
    for (int y = x; y < image_size - x - 1; y++) {
      // Store current cell in
      // temp variable
      int temp = image[x][y];

      // Move values from right to top
      image[x][y] = image[y][image_size - 1 - x];

      // Move values from bottom to right
      image[y][image_size - 1 - x]
          = image[image_size - 1 - x][image_size - 1 - y];

      // Move values from left to bottom
      image[image_size - 1 - x][image_size - 1 - y]
          = image[image_size - 1 - y][x];

      // Assign temp to left
      image[image_size - 1 - y][x] = temp;
    }
  }
}