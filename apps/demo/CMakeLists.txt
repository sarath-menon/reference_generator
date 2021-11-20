
add_executable(demo
src/main.cpp
)

target_include_directories(demo PUBLIC include)

target_link_libraries(demo PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
raptor_lib
)
