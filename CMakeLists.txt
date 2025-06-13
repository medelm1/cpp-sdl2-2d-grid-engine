cmake_minimum_required(VERSION 3.15)
project(2dGridEngine)

set(CMAKE_CXX_STANDARD 17)

# Add project include directory
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/SDL2/include
)

# Add third party library path
link_directories(
    ${CMAKE_SOURCE_DIR}/lib/SDL2/lib
)

# Add the source files
add_executable(2dGridEngine 

    src/audio/audio_manager.cpp

    src/graphics/sprite/animation.cpp
    src/graphics/sprite/animation_conroller.cpp
    src/graphics/sprite/frame.cpp
    src/graphics/sprite/sprite.cpp
    src/graphics/sprite/sprite_builder.cpp

    src/graphics/text/text_object.cpp
    src/graphics/text/text_renderer.cpp
    src/graphics/text/text_style.cpp

    src/graphics/texture_manager.cpp

    src/grid/grid.cpp
    src/grid/grid_cell.cpp
    src/grid/grid_size.cpp

    src/input/input_handler.cpp

    src/math/coordinate.cpp
    src/math/offset.cpp
    src/math/random.cpp
    src/math/scale.cpp
    src/math/size.cpp
    src/math/vector_2d.cpp

    src/game.cpp
    src/game_object.cpp

    src/main.cpp 
)

# Link libraries
target_link_libraries(
    2dGridEngine
    mingw32 SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf
)