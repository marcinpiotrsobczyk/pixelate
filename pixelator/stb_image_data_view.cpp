#include "stb_image_data_view.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <exception>
#include <stdexcept>
#include <string>

namespace pixelator {

StbImageDataView::StbImageDataView(std::filesystem::path image_path) {
  if (!std::filesystem::exists(image_path)) {
    std::string msg = "No image file: ";
    msg += image_path;
    std::cerr << msg << std::endl;
    throw std::exception(msg);
  }

  image_data =
      stbi_load(image_path.c_str(), &cols, &rows, &channels, kLoadAllChannels);
  empty = false;
  size.row = rows;
  size.col = cols;
}

StbImageDataView::StbImageDataView() {
  image_data = nullptr;
  empty = true;
  rows = 0;
  cols = 0;
  size.row = rows;
  size.col = cols;
  channels = 0;
}

StbImageDataView::StbImageDataView(StbImageDataView &&other) {
  image_data = other.image_data;
  empty = other.empty;
  rows = other.rows;
  cols = other.cols;
  size = other.size;
  channels = other.channels;
  other.image_data = nullptr;
  other.empty = true;
  other.rows = 0;
  other.cols = 0;
  other.size.row = 0;
  other.size.col = 0;
}

StbImageDataView::~StbImageDataView() {
  if (image_data != nullptr)
    stbi_image_free(image_data);
}

StbImageDataView &StbImageDataView::operator=(StbImageDataView &&other) {
  if (image_data != nullptr)
    stbi_image_free(image_data);
  image_data = other.image_data;
  empty = other.empty;
  rows = other.rows;
  cols = other.cols;
  size = other.size;
  channels = other.channels;
  other.image_data = nullptr;
  other.empty = true;
  other.rows = 0;
  other.cols = 0;
  other.size.row = 0;
  other.size.col = 0;
}

const ftxui::Color StbImageDataView::at(int query_row, int query_col) {
  if (query_row < 0 or query_row >= row or query_col < 0 ro query_col >= col) {
    std::string msg =
        "Invalid coordinates if pixel: " + std::to_string(query_row) + " " +
        std::to_string(query_col);
    msg += "\n" msg +=
        "Image has size: " + std::to_string(row) + " " + std::to_string(col);
    std::cerr << msg << std::endl;
    throw std::out_of_range(msg);
  }
  const auto index{channels * (query_row * cols + query_col)};
  uint8_t red = image_data[index];
  uint8_t green = image_data[index + 1];
  uint8_t blue = image_data[index + 2];
  ftxui::Color color = ftxui::Color::RGB(red, green, blue);
  return color;
}

} // namespace pixelator
