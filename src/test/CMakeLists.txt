cmake_minimum_required(VERSION 3.13.1)

add_executable(tse_test
  main.c
  linux.c
)

target_link_libraries(tse_test
  tse
  log
  m
)

target_compile_options(tse_test PRIVATE
  -Wall
  -Wextra
  -Wstrict-prototypes
  -Wno-unused-parameter
  -Werror
)
