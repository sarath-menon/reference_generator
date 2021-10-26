
add_executable(square_traj src/main.cpp)

target_include_directories(square_traj PUBLIC include)

target_link_libraries(square_traj PRIVATE
comm_lib
fastcdr 
fastrtps
)


