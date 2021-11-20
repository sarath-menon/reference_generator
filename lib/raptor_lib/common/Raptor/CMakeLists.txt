
add_library(raptor
src/Raptor.cpp
)

target_include_directories(raptor PUBLIC include)

target_link_libraries(raptor PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

