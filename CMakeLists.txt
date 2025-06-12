cmake_minimum_required(VERSION 3.15)
project(2dGridEngine)

set(CMAKE_CXX_STANDARD 17)

# Add project include directory
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/SDL2/include
)

# Add the SDL2 library path
link_directories(
    ${CMAKE_SOURCE_DIR}/lib/SDL2/lib
)

# Add the source files
add_executable(2dGridEngine 
    src/main.cpp 
    src/animation.cpp
    src/animation_conroller.cpp
    src/audio_manager.cpp
    src/coordinate.cpp
    src/frame.cpp
    src/game.cpp
    src/game_object.cpp
    src/grid.cpp
    src/grid_cell.cpp
    src/grid_size.cpp
    src/input_handler.cpp
    src/offset.cpp
    src/random.cpp
    src/scale.cpp
    src/size.cpp
    src/sprite.cpp
    src/sprite_builder.cpp
    src/text_object.cpp
    src/text_renderer.cpp
    src/text_style.cpp
    src/texture_manager.cpp
    src/vector_2d.cpp
)

# Link SDL2 libraries
target_link_libraries(
    2dGridEngine
    mingw32 SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf
)