# Adding welcome world plugin
add_library(welcome SHARED welcome.cpp)
target_link_libraries(welcome ${GAZEBO_LIBRARIES})

# Adding model plugin to move back and forth a model
set(HEADERS_BAF
    move_back_and_forth.hpp
    move_back_and_forth_private.hpp
)

set(SOURCES_BAF
    move_back_and_forth.cpp
)

add_library(back_and_forth SHARED ${SOURCES_BAF} ${HEADERS_BAF})
target_link_libraries(back_and_forth ${GAZEBO_LIBRARIES})