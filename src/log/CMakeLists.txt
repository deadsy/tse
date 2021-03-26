cmake_minimum_required(VERSION 3.13.1)

project(liblog VERSION 0.1 LANGUAGES C)

add_library(log STATIC
  log.c
)

target_include_directories(log PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(log PRIVATE
	-Wall
  -Wextra
  -Wstrict-prototypes
  -Wno-unused-parameter
  -Wpedantic
  -Werror
)
