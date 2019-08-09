cmake_minimum_required(VERSION 3.14)
project(Fdf_Alina C)

set(CMAKE_C_STANDARD 99)

link_directories(/usr/local/lib /home/alina/CLionProjects/grafics_part1/libft /home/alina/CLionProjects/minilibx)

add_executable(Fdf_Alina main.c map.h map_create.c error.c get_next_line.c draw.c fdf.h close_window.c keys.h gradient.c)

target_link_libraries(Fdf_Alina "/home/alina/CLionProjects/grafics_part1/libft/libft.a" "/home/alina/CLionProjects/minilibx/libmlx.a" "-lGLEW -lglfw -lGL -lm -lXext -lX11 -lbsd")