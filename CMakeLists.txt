cmake_minimum_required(VERSION 3.13)
project(gomoku)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${gomoku_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories( ${PROJECT_SOURCE_DIR}/media )

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

add_executable(gomoku
        headers/AiMove.hpp
        headers/ArtificialIntelligence.hpp
        headers/AvailableSpot.hpp
        headers/BoardState.hpp
        headers/Coordinates.hpp
        headers/GomokuMainBoard.hpp
        headers/MainHeader.hpp
        headers/SDLTextureClass.hpp
        headers/View.hpp
        src/ArtificialIntelligence.cpp
        src/AvailableSpot.cpp
        src/BoardState.cpp
        src/Coordinates.cpp
        src/GomokuMainBoard.cpp
        src/main.cpp
        src/SDLTextureClass.cpp
        src/ComputerPlayer.cpp
        src/APlayer.cpp
        src/HumanPlayer.cpp
        src/View.cpp src/Widget.cpp
        headers/Widget.hpp
        src/WidgetButton.cpp
        headers/WidgetButton.hpp
        src/WidgetButtonGroup.cpp
        headers/WidgetButtonGroup.hpp
        src/GomokuGame.cpp
        headers/GomokuGame.hpp
        src/WidgetLabel.cpp
        headers/WidgetLabel.hpp
        src/WidgetMenuField.cpp
        headers/WidgetMenuField.hpp
        src/HumanVsCompute.cpp
        headers/HumanVsCompute.hpp)

target_link_libraries(gomoku ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})