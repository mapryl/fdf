cmake_minimum_required(VERSION 3.14)
project(Fdf_Alina C)

set(CMAKE_C_STANDARD 99)

link_directories(/usr/local/lib /Users/mapryl/Desktop/Fdf_Alina/libft)

add_executable(Fdf_Alina main.c map.h map_create.c error.c get_next_line.c draw.c fdf.h close_window.c keys.h)

target_link_libraries(Fdf_Alina "/Users/mapryl/Desktop/Fdf_Alina/libft/libft.a" "libmlx.a" "-framework AppKit" "-framework OpenGL")