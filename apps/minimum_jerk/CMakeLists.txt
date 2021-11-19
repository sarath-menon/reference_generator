
add_executable(minimum_jerk 
src/main.cpp
)

target_include_directories(minimum_jerk  PUBLIC include)

target_link_libraries(minimum_jerk  PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
mueller_lib
)


