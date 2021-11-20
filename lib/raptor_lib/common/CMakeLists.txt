
# ###############################################################################
# # Library of complete quadcopter controllers
# ###############################################################################

add_library(common_lib INTERFACE)

target_link_libraries(common_lib INTERFACE
flight_manager
dds_manager
raptor
)

add_subdirectory(dds_manager)
add_subdirectory(flight_manager)
add_subdirectory(Raptor)
