
add_library(grasping_lib
src/grasper.cpp
src/go_to_pos.cpp
src/go_over_object.cpp
src/go_to_waypoint.cpp
src/mueller_controller.cpp
src/set_values.cpp
)

target_include_directories(grasping_lib PUBLIC include)

target_link_libraries(grasping_lib PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
mueller_lib
)
