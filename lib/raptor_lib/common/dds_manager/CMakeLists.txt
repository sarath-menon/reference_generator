
add_library(dds_manager
src/dds_manager.cpp
)

target_include_directories(dds_manager PUBLIC include)

target_link_libraries(dds_manager PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

