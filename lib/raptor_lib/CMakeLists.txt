# ###############################################################################
# # Library of complete quadcopter controllers
# ###############################################################################

add_library(raptor_lib INTERFACE)

target_link_libraries(raptor_lib INTERFACE
# behaviours_lib
common_lib
components_lib
)

add_subdirectory(common)
add_subdirectory(behaviours)
add_subdirectory(modules)

