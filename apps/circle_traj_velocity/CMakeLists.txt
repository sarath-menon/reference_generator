
add_executable(circle_traj_velocity src/main.cpp)

target_include_directories(circle_traj_velocity PUBLIC include)

target_link_libraries(circle_traj_velocity PRIVATE
comm_lib
fastcdr 
fastrtps
)


