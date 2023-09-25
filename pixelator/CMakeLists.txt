# TODO: Add your libraries here
# You must have the following libraries:
# - stb_image_data_view
# - drawer
# - image
# - pixelate_image
add_library(stb_image_data_view STATIC stb_image_data_view.cpp stb_image_data_view.hpp)
target_link_libraries(stb_image_data_view PRIVATE cxx_setup stb::stb)
target_include_directories(std_image_data_view INTERFACE ${PROJECT_SOURCE_DIR}/external)


if(BUILD_TESTING)
  include(GoogleTest)
  # TODO: Add your tests executable with all your tests here
  # Name it pixelator_tests.
  # Also use gtest_discover_tests(pixelator_tests)
  # to register them with CTest
endif()
