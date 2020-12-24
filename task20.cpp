//
// Created by marci_000 on 20.12.2020.
//

#include "task20.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <random>

void print_image(int id, const img_data& data) {
    if (id != -1)
        std::cout << "Tile " << id << ":" << std::endl;
    std::ofstream ofs("../data20_out.txt", std::ios::trunc);
    for (auto& row : data) {
        auto count = std::count_if(row.begin(), row.end(), [](auto it) {return it != ' ';});
        if (count == 0)
            break;
        std::cout << row << std::endl;
        ofs << row << std::endl;
    }
}

task20::task20() {
    std::ifstream ifs("../data20.txt");
    std::string line;
    std::regex rg(R"(Tile (\d+):)");

    while (std::getline(ifs, line)) {
        image img;
        if (line.empty())
            continue;
        std::smatch sm;
        if (!std::regex_match(line, sm, rg))
            throw "Invalid format!";

        img.title = sm[1];
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
        std::sort( img.rotated_flipped_images.begin(), img.rotated_flipped_images.end() );
        img.rotated_flipped_images.erase( std::unique( img.rotated_flipped_images.begin(), img.rotated_flipped_images.end() ), img.rotated_flipped_images.end() );

        // Sanity check
        if (images.contains(img.id))
            throw "Duplicated image?";

        images[img.id] = std::move(img);
    }

    classify_images();
}

void task20::classify_images() {
    for (auto& [id, im] : images) {
        for (size_t flipped_image_index = 0; flipped_image_index < im.rotated_flipped_images.size(); ++flipped_image_index) {
            auto& rotated_im = im.rotated_flipped_images[flipped_image_index];

            std::string top, right, bottom, left;

            top = rotated_im[0];
            bottom = rotated_im.back();
            for (auto& line : rotated_im) {
                right += line.back();
                left += *line.begin();
            }

            std::vector<edge> rot_img_edges;
            rot_img_edges.push_back(top);
            rot_img_edges.push_back(right);
            rot_img_edges.push_back(bottom);
            rot_img_edges.push_back(left);
            im.images_edges.push_back(rot_img_edges);

            // Insert this image edges as new entries.
            int n = 0;
            for (auto &edg : rot_img_edges) {
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
                classified_imgs_map[edg + sufix].insert(std::make_tuple(im.id, im.images_edges.size() - 1, true, n, flipped_image_index));
                n++;
            }

            // Insert this image edges as matching other entries.
            n = 0;
            for (auto &edg : rot_img_edges) {
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
                classified_imgs_map[edge_check].insert(std::make_tuple(im.id, im.images_edges.size() - 1, false, n, flipped_image_index));
                n++;
            }
        }
    }

    for (auto& [edge, id_set] : classified_imgs_map) {
        for (auto& id : id_set) {
            int id_1 = std::get<0>(id);
            for (auto id2 : id_set) {
                int id_2 = std::get<0>(id2);
                if (id_1 != id_2) {
                    bool is_org_image = std::get<2>(id2);
                    if (!is_org_image)
                    {
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

void task20::solve1() {

    // We have computed all possibly rotation of each image, then for each image rotation classified their edges to find
    // nearby images. Now we want to find edge images, to do this we find images for each rotations will have at most
    // 2 nearby images.

    // Variable for result.
    uint64_t total = 1;

    // Iterate each image.
    for (auto& [id, im] : images) {

        // Use map to count for each
        using nearby_image_count_for_rotation = int;
        std::unordered_map<rotate_image_index, nearby_image_count_for_rotation> im_index_count;
        for (const auto& rotated_img : im.nearby_imgs) {
            im_index_count[rotated_img.rot_index]++;
        }

        // Now find max count of nearby images for each rotation
        int max_nearbys_for_rotation = 0;
        for (auto& [rot_index, count] : im_index_count) {
            max_nearbys_for_rotation = std::max(max_nearbys_for_rotation, count);
        }
        if (max_nearbys_for_rotation == 2) {
            total *= id;
        }
    }

    // Correct answer: 17032646100079
    std::cout << "Solution 1: " << total << std::endl;
}

void task20::flip_horizontal(std::vector<row>& data)  // flips left-right
{
    for (int rr = 0; rr < data[0].size(); rr++)
    {
        for (int cc = 0; cc < data.size()/2; cc++)
        {
            int ccInv = data.size() - 1 - cc;
            std::swap<char>(data[rr][cc], data[rr][ccInv]);
        }
    }
}

void task20::flip_vertical(std::vector<row>& data)  // flips: bottom-up
{
    for (int cc = 0; cc < data[0].size(); cc++)
    {
        for (int rr = 0; rr < data.size()/2; rr++)
        {
            int rrInv = data.size() - 1 - rr;
            std::swap<char>(data[rr][cc], data[rrInv][cc]);
        }
    }
}

void task20::rotateMatrix(std::vector<row>& image)
{
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

void task20::solve2() {
    using img_x = int;
    using img_y = int;
    std::vector<std::tuple<image_id, rotate_image_index, img_x , img_y>> candidated_for_top_left;

    int side_size = sqrt(images.size());
    int img_side_size = images.begin()->second.rotated_flipped_images[0].size();

    for (auto& [id, im] : images) {

        // Use map to count for each
        using nearby_image_count_for_rotation = int;
        std::unordered_map<rotate_image_index, nearby_image_count_for_rotation> im_index_count;
        for (const auto& rotated_img : im.nearby_imgs) {
            im_index_count[rotated_img.rot_index]++;
        }

        // Now find max count of nearby images for each rotation
        int max_nearbys_for_rotation = 0;
        int max_nearby_rot_index = 0;
        for (auto& [rot_index, count] : im_index_count) {
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

    img_data entire_image, entire_image_max;
    entire_image.resize(side_size * (img_side_size+2));
    for (auto& row : entire_image) {
        row.resize((img_side_size+2) * side_size);
        std::fill(row.begin(), row.end(), ' ');
    }

    std::vector<std::vector<image_id>> image_matrix, image_matrix_max;
    image_matrix.resize(side_size);
    for (auto& row : image_matrix) {
        row.resize(side_size);
        std::fill(row.begin(), row.end(), -1);
    }

    std::queue<std::tuple<image_id, rotate_image_index , int, int>> img_queue;
    bool found = true;
    int max_correct = 0;

    for (auto& [top_left_img_id, top_left_rot_index, img_pos_x, img_pos_y] : candidated_for_top_left) {
        img_queue.push(std::make_tuple(top_left_img_id, top_left_rot_index, img_pos_x, img_pos_y));

        for (auto& row : entire_image)
            std::fill(row.begin(), row.end(), ' ');
        for (auto& row : image_matrix)
            std::fill(row.begin(), row.end(), -1);

        bool first_run = true;
        while(!img_queue.empty()) {
            auto [img_id, rot_index, img_row, img_col] = img_queue.front();
            img_queue.pop();

            image &img = images[img_id];

            if (first_run) {
                img_data &img_data_1 = img.rotated_flipped_images[rot_index];
                std::string title = std::to_string(img_id) + ":" + std::to_string(rot_index);
                std::copy(title.begin(), title.end(),
                          entire_image[img_row * (img_side_size + 1)].begin() + 1 +
                                  img_col * (img_side_size));
                for (std::size_t i = 0; i < img_data_1.size(); ++i) {
                    auto &row = img_data_1[i];
                    std::copy(row.begin(), row.end(),
                              entire_image[img_row * (img_side_size + 1) + i + 1].begin() + 1 +
                                      img_col * (img_side_size + 1));
                }
                image_matrix[img_row][img_col] = img_id;
                first_run = false;
            }

            for (auto& near_img : img.nearby_imgs) {
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

                        if (image_matrix[near_img_row][near_img_col] != -1)
                            continue;

                        bool repeated = false;
                        for (int ik1 = 0; ik1 < image_matrix.size(); ik1++) {
                            for (int ik2 = 0; ik2 < image_matrix[ik1].size(); ik2++) {
                                if (image_matrix[ik1][ik2] == near_img.id)
                                    repeated = true;
                            }
                        }
                        if (repeated) {
                            continue;
                        }

                        img_queue.push({near_img.id, near_img.rot_index, near_img_row, near_img_col});

                        image &img = images[near_img.id];
                        img_data &img_data_2 = img.rotated_flipped_images[near_img.rot_index];
                        std::string title = std::to_string(near_img.id) + ":" + std::to_string(near_img.rot_index);
                        std::copy(title.begin(), title.end(),
                                  entire_image[near_img_row * (img_side_size + 1)].begin() +
                                                              near_img_col * (img_side_size + 1));
                        for (std::size_t i = 0; i < img_data_2.size(); ++i) {
                            auto &row = img_data_2[i];
                            std::copy(row.begin(), row.end(),
                                      entire_image[near_img_row * (img_side_size + 1) + i + 1].begin() + 1 +
                                      near_img_col * (img_side_size + 1));
                        }
                        image_matrix[near_img_row][near_img_col] = img_id;
                    }
                }
            }
        }

        found = true;
        int max_c = 0;
        for (int ik1 = 0; ik1 < image_matrix.size(); ik1++) {
            for (int ik2 = 0; ik2 < image_matrix[ik1].size(); ik2++) {
                if (image_matrix[ik1][ik2] ==-1)
                    found = false;
                else
                    max_c++;
            }
        }
        if (max_c >= max_correct)
            entire_image_max = entire_image;
        max_correct = std::max(max_correct, max_c);
        if (found) {
            break;
        }

    }

    print_image(-1, entire_image_max);
    std::cout << "max correct is: " << max_correct << " of total: " << side_size*side_size << std::endl;

    // Correct answer: 17032646100079
    std::cout << "Solution 2: " << 0 << std::endl;
}
