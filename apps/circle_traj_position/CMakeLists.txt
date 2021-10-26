
add_executable(circle_traj_position src/main.cpp)

target_include_directories(circle_traj_position PUBLIC include)

target_link_libraries(circle_traj_position PRIVATE
comm_lib
fastcdr 
fastrtps
)


