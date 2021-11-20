
add_library(flight_manager
src/flight_manager.cpp
src/set_values.cpp
)

target_include_directories(flight_manager PUBLIC include)

target_link_libraries(flight_manager PRIVATE
comm_lib
components_lib
raptor
fastcdr 
fastrtps
yaml-cpp
)

