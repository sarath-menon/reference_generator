
add_library(behaviour
src/behaviour.cpp
)

target_include_directories(behaviour PUBLIC include)

target_link_libraries(behaviour PRIVATE
comm_lib
modules
fastcdr 
fastrtps
yaml-cpp
)

