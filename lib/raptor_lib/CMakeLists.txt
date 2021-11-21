# ###############################################################################
# # Library of complete quadcopter controllers
# ###############################################################################

add_library(raptor_lib INTERFACE)

target_link_libraries(raptor_lib INTERFACE
# behaviours_lib
common_lib
modules
)

add_subdirectory(common)
add_subdirectory(behaviours_lib)
add_subdirectory(modules)

