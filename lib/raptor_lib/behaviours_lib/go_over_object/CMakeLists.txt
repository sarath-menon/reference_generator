
add_library(go_over_object
src/go_over_object.cpp
src/set_values.cpp
)

target_include_directories(go_over_object PUBLIC include)

target_link_libraries(go_over_object PRIVATE
behaviour
modules
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

