
add_executable(grasping_first_version 
src/main.cpp
src/grasper.cpp
src/set_parameters.cpp
)

target_include_directories(grasping_first_version PUBLIC include)

target_link_libraries(grasping_first_version PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)


