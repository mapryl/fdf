cmake_minimum_required(VERSION 3.13.4)
project(Fdf_Alina C)

set(CMAKE_C_STANDARD 99)

link_directories(/usr/local/lib /Users/mflannel/Desktop/Fdf1408/libft)

add_executable(Fdf_Alina camera.c camera.h draw.c fdf.h get_next_line.c get_next_line.h gradient.c graphics.h keyboard_controls.c keyboard_controls.h
		keys.h line.c line.h main.c map.h map_create.c rotate.c rotate.h supporting_functions.c supporting_functions.h)

target_link_libraries(Fdf_Alina "/Users/mflannel/Desktop/Fdf1408/libft/libft.a" "libmlx.a" "-framework AppKit" "-framework OpenGL")