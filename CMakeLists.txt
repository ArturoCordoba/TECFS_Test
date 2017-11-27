cmake_minimum_required(VERSION 3.8)
project(TECFS_Test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp VideoHandler.cpp VideoHandler.h Singleton.cpp Singleton.h Menu.cpp Menu.h DataStructures/LinkedList.h DataStructures/Node.h VideoPlayer/MediaInfo.cpp VideoPlayer/MediaInfo.hpp VideoPlayer/StreamSelector.cpp VideoPlayer/StreamSelector.hpp VideoPlayer/UserInterface.cpp VideoPlayer/UserInterface.hpp VideoPlayer/VideoPlayerWindow.cpp VideoPlayer/VideoPlayerWindow.h)
add_executable(TECFS_Test ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TECFS_Test ${SFML_LIBRARIES})
endif()

find_package(sfeMovie REQUIRED)
if(sfeMovie_FOUND)
    include_directories(${SFEMOVIE_INCLUDE_DIR})
    target_link_libraries(TECFS_Test ${SFEMOVIE_LIBRARY})
endif()