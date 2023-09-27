#pragma once

#include "stb_image_data_view.hpp"

#include <ftxui/screen/color.hpp>

#include <filesystem>
#include <iostream>
#include <vector>

namespace pixelator {

constexpr int MAX_PIXELS = 32768;

class Image {
public:
  Image();
  Image(int desired_row, int desired_col);
  Image(const Image &other);
  Image(Image &&other);
  ~Image();
  Image &operator=(const Image &other);
  Image &operator=(Image &&other);

  bool empty() const { return _empty; }
  int rows() const { return _rows; }
  int cols() const { return _cols; }
  Size size() const { return _size; }

  ftxui::Color &at(int query_row, int query_col);

private:
  std::vector<ftxui::Color> color_data;
  bool _empty;
  int _rows;
  int _cols;
  Size _size;
};

// // Can be created empty
// pixelator::Image empty_image{};

// // Can be created with size provided.
// const auto rows{42};
// const auto cols{23};
// pixelator::Image image{rows, cols};

// // Has all the useful methods to get its size.
// empty_image.empty(); // Should be true.
// image.empty();       // Should be false.
// image.rows();        // Should be equal to rows.
// image.cols();        // Should be equal to cols.
// image.size();        // Should return pixelator::Size{rows, cols}.

// // Should provide read access to the colors.
// // All pixels must be initialized.
// image.at(0, 0) == ftxui::Color{};

// // Should provide write access to the colors.
// const ftxui::Color yellowish{ftxui::Color::RGB(255, 200, 100)};
// image.at(4, 2) = yellowish;
// image.at(4, 2) == yellowish; // Should be true.

// // We should be able to copy an image
// const pixelator::Image image_copy{image};
// image_copy.at(4, 2) == yellowish; // Should be true.

// // We should be able to move an image
// const pixelator::Image image_moved{std::move(image)};
// image_moved.at(4, 2) == yellowish; // Should be true.

} // namespace pixelator
