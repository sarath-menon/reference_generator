
add_executable(grasp_object
src/main.cpp
)

target_include_directories(grasp_object PUBLIC include)

target_link_libraries(grasp_object PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
grasping_lib
mueller_lib
)
