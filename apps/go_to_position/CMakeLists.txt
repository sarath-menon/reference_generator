
add_executable(go_to_position src/main.cpp)

target_include_directories(go_to_position PUBLIC include)

target_link_libraries(go_to_position PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)


