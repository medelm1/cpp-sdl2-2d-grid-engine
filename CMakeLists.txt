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

    src/audio/AudioManager.cpp

    src/graphics/sprite/Animation.cpp
    src/graphics/sprite/AnimationController.cpp
    src/graphics/sprite/Frame.cpp
    src/graphics/sprite/Sprite.cpp
    src/graphics/sprite/SpriteBuilder.cpp

    src/graphics/text/TextObject.cpp
    src/graphics/text/TextRenderer.cpp
    src/graphics/text/TextStyle.cpp

    src/graphics/TextureManager.cpp

    src/grid/Grid.cpp
    src/grid/GridCell.cpp
    src/grid/GridSize.cpp

    src/input/InputHandler.cpp

    src/math/Coordinate.cpp
    src/math/Offset.cpp
    src/math/Random.cpp
    src/math/Scale.cpp
    src/math/Size.cpp
    src/math/Vector2D.cpp

    src/Game.cpp
    src/GameObject.cpp

    src/main.cpp 
)

# Link libraries
target_link_libraries(
    2dGridEngine
    mingw32 SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf
)