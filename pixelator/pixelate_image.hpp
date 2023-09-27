#pragma once

#include "image.hpp"
#include "stb_image_data_view.hpp"

#include <ftxui/screen/color.hpp>

#include <filesystem>
#include <iostream>
#include <vector>

namespace pixelator {

Image PixelateImage(const StbImageDataView &image_data_view, Size smaller_size);

// // Use the test image provided in the project skeleton for tests.
// const auto kImagePath{"../../tui_pixelator/test_data/test.png"};
// const pixelator::StbImageDataView image{kImagePath};
// const auto pixelated_image =
//     pixelator::PixelateImage(image, pixelator::Size{3, 2});

// // Note that if the size is larger than the original image the method returns
// // the pixelator::Image object of the same size as the input image with all the
// // pixels having the same values as the original image.

// // static_cast<float>(number) converts (aka "casts") a number to float.
// const auto factor_cols = smaller_size.cols / static_cast<float>(image.cols());
// const auto factor_rows = smaller_size.rows / static_cast<float>(image.rows());
// const auto smallest_factor = std::min(factor_cols, factor_rows);

// int Scale(int number, float factor) {
//   return static_cast<int>(number * factor);
// }

} // namespace pixelator
