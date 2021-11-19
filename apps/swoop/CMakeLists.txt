
add_executable(swoop
src/main.cpp
)

target_include_directories(swoop PUBLIC include)

target_link_libraries(swoop PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
grasping_lib
mueller_lib
)
