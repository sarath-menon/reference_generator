
add_library(motion_controller
src/go_to_pos.cpp
src/motion_controller.cpp
src/mueller_controller.cpp
src/set_values.cpp
)

target_include_directories(motion_controller PUBLIC include)

target_link_libraries(motion_controller PRIVATE
mueller_controller
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

