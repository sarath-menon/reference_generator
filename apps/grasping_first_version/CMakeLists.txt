
add_executable(main_normal
src/main_normal.cpp
src/grasper.cpp
src/set_parameters.cpp
src/go_to_pos.cpp
src/go_to_object.cpp
src/go_to_waypoint.cpp
src/mueller_controller.cpp
src/RapidTrajectoryGenerator.cpp
src/SingleAxisTrajectory.cpp
)

target_include_directories(main_normal PUBLIC include mueller_include)

target_link_libraries(main_normal PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)


add_executable(main_mueller
src/main_mueller.cpp
src/grasper.cpp
src/set_parameters.cpp
src/go_to_pos.cpp
src/go_to_object.cpp
src/go_to_waypoint.cpp
src/mueller_controller.cpp
src/RapidTrajectoryGenerator.cpp
src/SingleAxisTrajectory.cpp
)

target_include_directories(main_mueller PUBLIC include mueller_include)

target_link_libraries(main_mueller PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)


