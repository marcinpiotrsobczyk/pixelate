#include "image.hpp"

#include <exception>
#include <stdexcept>
#include <utility>

namespace pixelator {

Image::Image(int desired_rows, int desired_cols) {
  if (desired_rows < 0 or desired_cols < 0 or desired_rows >= MAX_PIXELS or
      desired_cols >= desired_rows) {
    std::string msg =
        "Desired image is too large: " + std::to_string(desired_rows) + " " +
        std::to_string(desired_cols);
    std::cerr << msg << std::endl;
    throw std::exception(msg);
  }
  color_data.resize(desired_rows * desired_cols);
  empty = false;
  rows = desired_rows;
  cols = desired_cols;
  size.row = rows;
  size.col = cols;
}

Image::Image() {
  empty = true;
  rows = 0;
  cols = 0;
  size.row = rows;
  size.col = cols;
}

Image::~Image() {}

Image::Image(const Image &other) {
  color_data = other.color_data;
  empty = other.empty;
  rows = other.rows;
  cols = other.cols;
  size = other.size;
}

Image::Image(Image &&other) {
  color_data = std::move(other.color_data);
  empty = other.empty;
  rows = other.rows;
  cols = other.cols;
  size = other.size;
  other.empty = true;
  other.rows = 0;
  other.cols = 0;
  other.size.row = 0;
  other.size.col = 0;
}

Image &Image::operator=(const Image &other) {
  color_data = other.color_data;
  empty = other.empty;
  rows = other.rows;
  cols = other.cols;
  size = other.size;
}

Image &Image::operator=(Image &&other) {
  color_data = std::move(other.color_data);
  empty = other.empty;
  rows = other.rows;
  cols = other.cols;
  size = other.size;
  other.empty = true;
  other.rows = 0;
  other.cols = 0;
  other.size.row = 0;
  other.size.col = 0;
}

ftxui::Color &Image::at(int query_row, int query_col) {
  if (query_row < 0 or query_row >= row or query_col < 0 ro query_col >= col) {
    std::string msg =
        "Invalid coordinates if pixel: " + std::to_string(query_row) + " " +
        std::to_string(query_col);
    msg += "\n" msg +=
        "Image has size: " + std::to_string(row) + " " + std::to_string(col);
    std::cerr << msg << std::endl;
    throw std::out_of_range(msg);
  }
  const auto index{query_row * cols + query_col};
  return color_data.at(index);
}

} // namespace pixelator
