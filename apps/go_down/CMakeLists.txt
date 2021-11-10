
add_executable(go_down src/main.cpp)

target_include_directories(go_down PUBLIC include)

target_link_libraries(go_down PRIVATE
comm_lib
fastcdr 
fastrtps
)


