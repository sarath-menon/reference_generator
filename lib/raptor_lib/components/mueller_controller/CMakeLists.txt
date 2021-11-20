
add_library(mueller_controller
src/RapidTrajectoryGenerator.cpp
src/SingleAxisTrajectory.cpp
)

target_include_directories(mueller_controller PUBLIC include)

target_link_libraries(mueller_controller PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

