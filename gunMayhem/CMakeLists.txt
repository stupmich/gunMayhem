cmake_minimum_required(VERSION 3.7)
project(gunMayhem)

set(CMAKE_CXX_STANDARD 20)

add_executable(gunMayhem src/main.cpp headers/Game.h src/Game.cpp headers/Player.h src/Player.cpp headers/Bullet.h src/Bullet.cpp headers/Weapon.h src/Weapon.cpp)

include_directories(headers /usr/include c:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(gunMayhem ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()