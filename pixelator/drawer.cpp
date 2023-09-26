#include "drawer.hpp"
#include "stb_image_data_view.hpp"

#include <ftxui/screen/color.hpp>

#include <exception>
#include <iostream>
#include <string>

namespace pixelator {


Drawer::Drawer(ftxui::Dimensions desired_dimensions) {
    dimensions = desired_dimensions;
    rows = dimensions.dimy;
    cols = dimensions.dimx;
    size.row = rows;
    size.col = cols;

    screen = ftxui::Screen::Create(dimensions);
}

void Drawer::Set(Image image_to_set) {
    image = image_to_set;
}

void Drawer::Draw() {
    if (size != image.size()) {
        std::string msg = "Screen size and image size don't match";
        msg += "Screen size is " + std::to_string(size.row) + " " + std::to_string(size.col);
        msg += "Image size is " + std::to_string(image.size().row) + " " + std::to_string(image.size().col);
        std::cerr << msg << std::endl;
        throw std::exception(msg);
    }

    for (int i=0; i < size.row; ++i) {
      for (int j=0; j < size.col; ++j) {
        auto color = image.at(i, j);
        auto &pixel = screen.PixelAt(j, i);
        pixel.background_color = color;
        pixel.character = ' ';
      }
    }

  screen.Print();
}


} // namespace pixelator
