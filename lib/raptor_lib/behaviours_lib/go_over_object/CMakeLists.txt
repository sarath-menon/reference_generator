
add_library(motion_controller
src/raptor.cpp
src/set_values.cpp
)

target_include_directories(motion_controller PUBLIC include)

target_link_libraries(motion_controller PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

