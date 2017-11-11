cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(speed-of-sound-cli)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")

add_library(speed-of-sound
  lib/speed-of-sound/src/environment.cc
  lib/speed-of-sound/src/speed-of-sound-theory.cc
  lib/speed-of-sound/src/speed-of-sound.cc)
set_target_properties(speed-of-sound PROPERTIES LINKER_LANGUAGE CXX)
add_executable(speed-of-sound-cli
  src/speed-of-sound-cli.cc)
target_link_libraries(speed-of-sound-cli PRIVATE 
  speed-of-sound)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/lib/speed-of-sound/src)
add_dependencies(speed-of-sound-cli speed-of-sound)
