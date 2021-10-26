
add_executable(circle_traj src/main.cpp)

target_include_directories(circle_traj PUBLIC include)

target_link_libraries(circle_traj PRIVATE
comm_lib
fastcdr 
fastrtps
)


