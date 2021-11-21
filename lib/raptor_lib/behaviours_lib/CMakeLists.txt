
# ###############################################################################
# # Library of behaviours
# ###############################################################################


add_library(behaviours_lib INTERFACE)

target_link_libraries(behaviours_lib INTERFACE
go_over_object
overhead_grasp
)

add_subdirectory(go_over_object)
add_subdirectory(overhead_grasp)