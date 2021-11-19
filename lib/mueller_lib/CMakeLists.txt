
add_library(mueller_lib
src/RapidTrajectoryGenerator.cpp
src/SingleAxisTrajectory.cpp
)

target_include_directories(mueller_lib PUBLIC include)

target_link_libraries(mueller_lib PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

