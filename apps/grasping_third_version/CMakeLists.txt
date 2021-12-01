
add_executable(grasping_third_version 
src/main.cpp
src/grasper.cpp
src/set_parameters.cpp
src/go_near_object.cpp
src/departure.cpp
src/go_to_pos.cpp
src/grip.cpp
src/RapidTrajectoryGenerator.cpp
src/SingleAxisTrajectory.cpp
)

target_include_directories(grasping_third_version PUBLIC include)

target_link_libraries(grasping_third_version PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)


