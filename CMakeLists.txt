cmake_minimum_required(VERSION 3.13.4)
project(Fdf_Alina C)

set(CMAKE_C_STANDARD 99)

link_directories(/usr/local/lib /Users/mflannel/Desktop/grafics_part1/libft)

add_executable(Fdf_Alina camera.h camera.c draw.c errors.h fdf.h gradient.c graphics.h keyboard_controls.h keyboard_controls.c keys.h line.h line.c	main.c map_create.c map.h rotate.h rotate.c supporting_functions.h supporting_functions.c)

target_link_libraries(Fdf_Alina "/Users/mflannel/Desktop/grafics_part1/libft/libft.a" "libmlx.a" "-framework AppKit" "-framework OpenGL")