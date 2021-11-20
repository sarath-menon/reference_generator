
# ###############################################################################
# # Library of complete quadcopter controllers
# ###############################################################################

add_library(common_lib INTERFACE)

target_link_libraries(common_lib INTERFACE
flight_manager
raptor
)


add_subdirectory(FlightManager)
add_subdirectory(Raptor)