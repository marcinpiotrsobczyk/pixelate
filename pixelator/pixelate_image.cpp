#include "pixelate_image.hpp"

#include <algorithm>
#include <cfenv>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace pixelator {

Image PixelateImage(const StbImageDataView &image_data_view,
                    Size smaller_size) {
  if (smaller_size.row <= 0 or smaller_size.col <= 0) {
    std::string msg =
        "Scaled size must be positive: " + std::to_string(smaller_size.row) +
        " " + std::to_string(smaller_size.col);
    std::cerr << msg << std::endl;
    throw std::logic_error(msg);
  }

  if (smaller_size.row > image_data_view.rows() and
      smaller_size.col > image_data_view.cols()) {
    Image image(image_data_view.rows(), image_data_view.cols());
    for (int i = 0; i < image.rows(); ++i)
      for (int j = 0; j < image.cols(); ++j)
        image.at(i, j) = image_data_view.at(i, j);
    return image;
  }

  const double factor_row =
      smaller_size.row / static_cast<double>(image_data_view.rows());
  const double factor_col =
      smaller_size.col / static_cast<double>(image_data_view.cols());
  const double smallest_factor = std::min(factor_row, factor_col);
  Size new_size;
  new_size.row = static_cast<int>(image_data_view.rows() * smallest_factor);
  new_size.col = static_cast<int>(image_data_view.cols() * smallest_factor);
  if (new_size.row <= 0 or new_size.col <= 0) {
    std::string msg = "Scaled size with aspect must be positive: " +
                      std::to_string(new_size.row) + " " +
                      std::to_string(new_size.col);
    std::cerr << msg << std::endl;
    throw std::logic_error(msg);
  }

  Image image(new_size.row, new_size.col);
  for (int i = 0; i < image.rows(); ++i)
    for (int j = 0; j < image.cols(); ++j) {
      double total_weight = 0.0;
      std::fesetround(FE_DOWNWARD);
      double x_double_min = j / smallest_factor;
      double y_double_min = i / smallest_factor;
      int x_min = std::lrint(x_double_min);
      int y_min = std::lrint(y_double_min);
      std::fesetround(FE_UPWARD);
      double x_double_max = (j + 1) / smallest_factor;
      double y_double_max = (i + 1) / smallest_factor;
      int x_max = std::lrint(x_double_max);
      int y_max = std::lrint(y_double_max);
      std::fesetround(FE_DOWNWARD);

      ftxui::Color target_pixel_color;
      for (int query_col = x_min; query_col < x_max; ++query_col)
        for (int query_row = y_min; query_row < y_max; ++query_row) {
          double this_pixel_weight = 1.0;
          if (query_col == x_min)
            this_pixel_weight *= (x_min + 1 - x_double_min);
          if (query_col == x_max)
            this_pixel_weight *= (x_double_max - x_max + 1);
          if (query_row == y_min)
            this_pixel_weight *= (y_min + 1 - y_double_min);
          if (query_row == y_max)
            this_pixel_weight *= (y_double_max - y_max + 1);
          ftxui::Color this_pixel_color =
              image_data_view.at(query_row, query_col);
          total_weight += this_pixel_weight;
          target_pixel_color =
              ftxui::Color::Interpolate(this_pixel_weight / total_weight,
                                        target_pixel_color, this_pixel_color);
        }
      image.at(i, j) = target_pixel_color;
    }
  return image;
}

} // namespace pixelator
