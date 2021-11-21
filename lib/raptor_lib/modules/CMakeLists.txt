# ###############################################################################
# # Library of modules
# ###############################################################################


add_library(modules INTERFACE)

target_link_libraries(modules INTERFACE
mueller_controller
waypoint_tracker
motion_controller
)

add_subdirectory(mueller_controller)
add_subdirectory(waypoint_tracker)
add_subdirectory(motion_controller)

