file( GLOB SOLVER_SOURCES test0.cpp ${CMAKE_SOURCE_DIR}/sca/*.cpp ${CMAKE_SOURCE_DIR}/sca/parser/*.cpp )
add_executable( test0 ${SOLVER_SOURCES} )

if(WIN32)
target_link_libraries( test0 wsock32 ws2_32 )
endif()

add_test( NAME Test0 COMMAND test0 WORKING_DIRECTORY ${CMAKE_BINARY_DIR} )