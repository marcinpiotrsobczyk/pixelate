#pragma once

#include <ftxui/screen/color.hpp>
#include <stb/stb_image.h>

#include <filesystem>
#include <iostream>

namespace pixelator {

// There must be a size struct in some file, either this or some other header
struct Size {
  int row;
  int col;
};

static constexpr auto kLoadAllChannels{0};

// // Some path to an image on disk.
// const std::filesystem::path image_path{...};
// // We must be able to load the image from a path and store its data
// // internally in the image object.
// // We should also be able to create an empty image
// pixelator::StbImageDataView image{image_path};
// pixelator::StbImageDataView empty_image{};

class StbImageDataView {
public:
  StbImageDataView(std::filesystem::path image_path);
  StbImageDataView();
  StbImageDataView(const StbImageDataView &other) = delete;
  StbImageDataView(StbImageDataView &&other);
  ~StbImageDataView();
  StbImageDataView &operator=(const StbImageDataView &other) = delete;
  StbImageDataView &operator=(StbImageDataView &&other);

  bool empty() const { return _empty; }
  int rows() const { return _rows; }
  int cols() const { return _cols; }
  Size size() const { return _size; }

  const ftxui::Color at(int query_row, int query_col) const;

private:
  stbi_uc *image_data;
  bool _empty;
  int _rows;
  int _cols;
  Size _size;
  int _channels;
};

// // We must have simple accessors
// const pixelator::Size size = image.size();
// const int rows = image.rows();
// const int cols = image.cols();
// // Returns true if and only if the image size is 0.
// const bool empty = image.empty();

// // We must be able to get a color by row and column.
// // Note that we return a copy of the color here.
// int row = 4;
// int col = 2;
// const ftxui::Color color = image.at(row, col);

// // We should be able to move the images
// pixelator::StbImageDataView other_image = std::move(image);
// empty_image = std::move(image);

// // ❌ The following code must NOT compile, copying the StbImageDataView should
// // NOT be allowed
// pixelator::StbImageDataView other_image = image; // ❌ Must not compile
// empty_image = image;                             // ❌ Must not compile

// At the end, the StbImageDataView objects should free the underlying memory
// upon
//                 destruction.

} // namespace pixelator
