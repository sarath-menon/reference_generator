
add_executable(circle
src/main.cpp
)

target_include_directories(circle PUBLIC include)

target_link_libraries(circle PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
mueller_lib
raptor_lib
)
