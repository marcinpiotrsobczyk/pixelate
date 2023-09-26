#include "image.hpp"
#include "stb_image_data_view.hpp"

#include <ftxui/screen/color.hpp>
#include <stb/stb_image.h>

#include <string>

namespace pixelator {


class Drawer {
public:
  Drawer(ftxui::Dimensions desired_dimensions);


  int rows() { return rows; }
  int cols() { return cols; }
  Size size() { return size; }

  void Set(Image image);
  void Draw();
  std::string ToSTring();

private:
  ftxui::Dimensions dimensions;
  int rows;
  int cols;
  Size size;
  ftxui::Screen screen;
  Image image;
};

// // We should be able to create a drawer either of fixed size or of the maximum
// // size that the terminal is capable of. Read the ftxui docs to understand these
// // parameters better.
// pixelator::Drawer full_screen_drawer{ftxui::Dimension::Full()};
// pixelator::Drawer fixed_screen_drawer{ftxui::Dimension::Fixed(42)};

// // All the following must be true.
// // Note that the number of cols should be twice the number of rows, see
// // explanation below the code block.
// fixed_screen_drawer.rows() == 42;
// fixed_screen_drawer.cols() == 84;
// fixed_screen_drawer.size() == Size{42, 84};

// // We should be able to set a pixelated image to our drawer.
// const auto kImagePath{"../../tui_pixelator/test_data/test.png"};
// const pixelator::StbImageDataView image{kImagePath};
// const auto pixelated_image =
//     pixelator::PixelateImage(image, pixelator::Size{3, 2});
// full_screen_drawer.Set(pixelated_image);

// // We should be able to print to the terminal by calling ftxui::Screen functions
// // under the hood.
// full_screen_drawer.Draw();     // Draws to the terminal.
// full_screen_drawer.ToString(); // Prints to string, used for testing.


} // namespace pixelator
