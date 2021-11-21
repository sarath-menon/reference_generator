
add_library(waypoint_tracker
src/waypoint_tracker.cpp
src/set_values.cpp
)

target_include_directories(waypoint_tracker PUBLIC include)

target_link_libraries(waypoint_tracker PRIVATE
motion_controller
comm_lib
raptor
fastcdr 
fastrtps
yaml-cpp
)

