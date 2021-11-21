
add_library(overhead_grasp
src/overhead_grasp.cpp
src/set_values.cpp
)

target_include_directories(overhead_grasp PUBLIC include)

target_link_libraries(overhead_grasp PRIVATE
behaviour
modules
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

