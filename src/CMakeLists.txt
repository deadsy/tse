cmake_minimum_required(VERSION 3.13.1)

project(libtse VERSION 0.1 LANGUAGES C)

add_library(tse STATIC
  lut.c
  midi.c
  test.c
)

target_compile_options(tse PRIVATE
	-Wall
  -Wextra
  -Wstrict-prototypes
  -Wno-unused-parameter
  -Wpedantic
  -Werror
)

