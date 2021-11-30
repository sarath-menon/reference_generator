
add_executable(grasping_second_version 
src/main.cpp
src/grasper.cpp
src/set_parameters.cpp
src/go_near_object.cpp
src/departure.cpp
src/go_to_pos.cpp
src/grip.cpp
)

target_include_directories(grasping_second_version PUBLIC include)

target_link_libraries(grasping_second_version PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)


