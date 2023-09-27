#include "drawer.hpp"
#include "stb_image_data_view.hpp"

#include <stdexcept>
#include <iostream>
#include <string>

namespace pixelator {


Drawer::Drawer(ftxui::Dimensions desired_dimensions)
  : screen(ftxui::Screen::Create(dimensions)) {
    dimensions = desired_dimensions;
    _rows = dimensions.dimy;
    _cols = dimensions.dimx;
    _size.row = _rows;
    _size.col = _cols;
}

void Drawer::Set(Image image_to_set) {
    image = image_to_set;
}

void Drawer::Draw() {
    if ( _size.row!=image.size().row or _size.col!=image.size().col ) {
        std::string msg = "Screen size and image size don't match";
        msg += "\n";
        msg += "Screen size is " + std::to_string(_size.row) + " " + std::to_string(_size.col);
        msg += "\n";
        msg += "Image size is " + std::to_string(image.size().row) + " " + std::to_string(image.size().col);
        std::cerr << msg << std::endl;
        throw std::logic_error(msg);
    }

    for (int i=0; i < _size.row; ++i) {
      for (int j=0; j < _size.col; ++j) {
        auto color = image.at(i, j);
        auto &pixel = screen.PixelAt(j, i);
        pixel.background_color = color;
        pixel.character = ' ';
      }
    }

  screen.Print();
}


} // namespace pixelator
