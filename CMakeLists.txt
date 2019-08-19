cmake_minimum_required(VERSION 3.13.4)
project(Fdf_Alina C)

set(CMAKE_C_STANDARD 99)

link_directories(/usr/local/lib /Users/mflannel/Desktop/grafics_part1/libft)

add_executable(Fdf_Alina main.c map.h map_create.c draw.c fdf.h keys.h gradient.c camera.c camera.h graphics.h keyboard_controls.c keyboard_controls.h rotate.c rotate.h supporting_functions.c supporting_functions.h line.c line.h errors.h)

target_link_libraries(Fdf_Alina "/Users/mflannel/Desktop/grafics_part1/libft/libft.a" "libmlx.a" "-lmlx -lm -lft -framework OpenGL -framework AppKit")