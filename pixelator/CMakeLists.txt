# TODO: Add your libraries here
# You must have the following libraries:
# - stb_image_data_view
# - drawer
# - image
# - pixelate_image
add_library(stb_image_data_view STATIC stb_image_data_view.cpp stb_image_data_view.hpp)
target_link_libraries(stb_image_data_view PRIVATE cxx_setup stb::stb ftxui::screen)
target_include_directories(stb_image_data_view INTERFACE ${PROJECT_SOURCE_DIR}/external)

add_library(image STATIC image.cpp image.hpp)
target_link_libraries(image PRIVATE cxx_setup stb::stb ftxui::screen stb_image_data_view)
target_include_directories(image INTERFACE ${PROJECT_SOURCE_DIR}/external)

add_library(pixelate_image STATIC pixelate_image.cpp pixelate_image.hpp)
target_link_libraries(pixelate_image PRIVATE cxx_setup stb::stb ftxui::screen stb_image_data_view image)
target_include_directories(pixelate_image INTERFACE ${PROJECT_SOURCE_DIR}/external)

add_library(drawer STATIC drawer.cpp drawer.hpp)
target_link_libraries(drawer PRIVATE cxx_setup stb::stb ftxui::screen stb_image_data_view image)
target_include_directories(drawer INTERFACE ${PROJECT_SOURCE_DIR}/external)


if(BUILD_TESTING)
  include(GoogleTest)
  # TODO: Add your tests executable with all your tests here
  # Name it pixelator_tests.
  # Also use gtest_discover_tests(pixelator_tests)
  # to register them with CTest
endif()
