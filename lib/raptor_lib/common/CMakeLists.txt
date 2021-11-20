
add_library(common_lib
src/FlightManager.cpp
)

target_include_directories(common_lib PUBLIC include)

target_link_libraries(common_lib PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

