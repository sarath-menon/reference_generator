# ###############################################################################
# # Library of modules
# ###############################################################################


add_library(utilities INTERFACE)

target_link_libraries(utilities INTERFACE
timer
)

add_subdirectory(timer)
