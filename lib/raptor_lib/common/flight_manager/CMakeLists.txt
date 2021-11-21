
add_library(flight_manager
src/flight_manager.cpp
src/set_values.cpp
src/add_behaviour.cpp
)

target_include_directories(flight_manager PUBLIC include)

target_link_libraries(flight_manager PRIVATE
comm_lib
modules
behaviour
raptor
fastcdr 
fastrtps
yaml-cpp
)

