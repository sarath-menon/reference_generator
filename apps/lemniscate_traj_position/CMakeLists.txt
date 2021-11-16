
add_executable(lemniscate_pos_traj src/main.cpp)

target_include_directories(lemniscate_pos_traj PUBLIC include)

target_link_libraries(lemniscate_pos_traj PRIVATE
comm_lib
fastcdr 
fastrtps
)


