
add_executable(minimum_jerk_new
src/main.cpp
src/RapidTrajectoryGenerator.cpp
src/SingleAxisTrajectory.cpp
)

target_include_directories(minimum_jerk_new  PUBLIC include)

target_link_libraries(minimum_jerk_new  PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)


