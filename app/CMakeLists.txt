cmake_minimum_required(VERSION 3.20.0)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
find_package(Zephyr REQUIRED HINTS ${ZEPHYR_BASE})
project(my_zephyr_app)

target_sources(app PRIVATE src/main.c)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../drivers/our_driver ${CMAKE_CURRENT_BINARY_DIR}/drivers/our_driver)
