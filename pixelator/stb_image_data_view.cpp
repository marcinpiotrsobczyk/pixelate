#define STB_IMAGE_IMPLEMENTATION
#include "stb_image_data_view.hpp"

#include <stdexcept>
#include <string>

namespace pixelator {

StbImageDataView::StbImageDataView(std::filesystem::path image_path) {
  if (!std::filesystem::exists(image_path)) {
    std::string msg = "No image file: ";
    msg += image_path;
    std::cerr << msg << std::endl;
    throw std::logic_error(msg);
  }

  image_data = stbi_load(image_path.c_str(), &_cols, &_rows, &_channels,
                         kLoadAllChannels);
  _empty = false;
  _size.row = _rows;
  _size.col = _cols;
}

StbImageDataView::StbImageDataView() {
  image_data = nullptr;
  _empty = true;
  _rows = 0;
  _cols = 0;
  _size.row = _rows;
  _size.col = _cols;
  _channels = 0;
}

StbImageDataView::StbImageDataView(StbImageDataView &&other) {
  image_data = other.image_data;
  _empty = other._empty;
  _rows = other._rows;
  _cols = other._cols;
  _size = other._size;
  _channels = other._channels;
  other.image_data = nullptr;
  other._empty = true;
  other._rows = 0;
  other._cols = 0;
  other._size.row = 0;
  other._size.col = 0;
}

StbImageDataView::~StbImageDataView() {
  if (image_data != nullptr)
    stbi_image_free(image_data);
}

StbImageDataView &StbImageDataView::operator=(StbImageDataView &&other) {
  if (image_data != nullptr)
    stbi_image_free(image_data);
  image_data = other.image_data;
  _empty = other._empty;
  _rows = other._rows;
  _cols = other._cols;
  _size = other._size;
  _channels = other._channels;
  other.image_data = nullptr;
  other._empty = true;
  other._rows = 0;
  other._cols = 0;
  other._size.row = 0;
  other._size.col = 0;
  return *this;
}

const ftxui::Color StbImageDataView::at(int query_row, int query_col) const {
  if (query_row < 0 or query_row >= _rows or query_col < 0 or
      query_col >= _cols) {
    std::string msg =
        "Invalid coordinates if pixel: " + std::to_string(query_row) + " " +
        std::to_string(query_col);
    msg += "\n";
    msg += "Image has size: " + std::to_string(_rows) + " " +
           std::to_string(_cols);
    std::cerr << msg << std::endl;
    throw std::out_of_range(msg);
  }
  const auto index{_channels * (query_row * _cols + query_col)};
  uint8_t red = image_data[index];
  uint8_t green = image_data[index + 1];
  uint8_t blue = image_data[index + 2];
  ftxui::Color color = ftxui::Color::RGB(red, green, blue);
  return color;
}

} // namespace pixelator
