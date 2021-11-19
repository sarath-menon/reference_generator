
add_executable(grasping_first_version 
src/main.cpp
src/grasper.cpp
src/set_parameters.cpp
src/go_to_pos.cpp
src/go_to_object.cpp
src/go_to_waypoint.cpp
src/mueller_controller.cpp
src/RapidTrajectoryGenerator.cpp
src/SingleAxisTrajectory.cpp
)

target_include_directories(grasping_first_version PUBLIC include mueller_include)

target_link_libraries(grasping_first_version PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)


