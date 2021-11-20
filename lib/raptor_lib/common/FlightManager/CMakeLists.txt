
add_library(flight_manager
src/FlightManager.cpp
)

target_include_directories(flight_manager PUBLIC include)

target_link_libraries(flight_manager PRIVATE
comm_lib
fastcdr 
fastrtps
yaml-cpp
)

