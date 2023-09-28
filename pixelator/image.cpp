#include "image.hpp"

#include <stdexcept>
#include <utility>

namespace pixelator {

Image::Image(int desired_row, int desired_col) {
  if (desired_row < 0 or desired_col < 0 or desired_row >= MAX_PIXELS or
      desired_col >= MAX_PIXELS) {
    std::string msg =
        "Desired image is too large: " + std::to_string(desired_row) + " " +
        std::to_string(desired_col);
    std::cerr << msg << std::endl;
    throw std::logic_error(msg);
  }
  color_data.resize(desired_row * desired_col);
  _empty = false;
  _rows = desired_row;
  _cols = desired_col;
  _size.row = _rows;
  _size.col = _cols;
}

Image::Image() {
  _empty = true;
  _rows = 0;
  _cols = 0;
  _size.row = _rows;
  _size.col = _cols;
}

Image::~Image() {}

Image::Image(const Image &other) {
  color_data = other.color_data;
  _empty = other._empty;
  _rows = other._rows;
  _cols = other._cols;
  _size = other._size;
}

Image::Image(Image &&other) {
  color_data = std::move(other.color_data);
  _empty = other._empty;
  _rows = other._rows;
  _cols = other._cols;
  _size = other._size;
  other._empty = true;
  other._rows = 0;
  other._cols = 0;
  other._size.row = 0;
  other._size.col = 0;
}

Image &Image::operator=(const Image &other) {
  color_data = other.color_data;
  _empty = other._empty;
  _rows = other._rows;
  _cols = other._cols;
  _size = other._size;
  return *this;
}

Image &Image::operator=(Image &&other) {
  color_data = std::move(other.color_data);
  _empty = other._empty;
  _rows = other._rows;
  _cols = other._cols;
  _size = other._size;
  other._empty = true;
  other._rows = 0;
  other._cols = 0;
  other._size.row = 0;
  other._size.col = 0;
  return *this;
}

ftxui::Color &Image::at(int query_row, int query_col) {
  if (query_row < 0 or query_row >= _rows or query_col < 0 or query_col >= _cols) {
    std::string msg =
        "Invalid coordinates if pixel: " + std::to_string(query_row) + " " +
        std::to_string(query_col);
    msg += "\n";
    msg += "Image has size: " + std::to_string(_rows) + " " + std::to_string(_cols);
    std::cerr << msg << std::endl;
    throw std::out_of_range(msg);
  }
  const auto index{query_row * _cols + query_col};
  return color_data.at(index);
}

} // namespace pixelator
