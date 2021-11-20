# ###############################################################################
# # Library of components
# ###############################################################################


add_library(components_lib INTERFACE)

target_link_libraries(components_lib INTERFACE
mueller_controller
)

add_subdirectory(mueller_controller)

