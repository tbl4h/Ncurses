cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(ncurses VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# should we use our own math functions
option(USE_MYMATH "Use ncurses provided math implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# set CMAKE_INSTALL_PREFIX
#set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/bin")

# add the MathFunctions library
if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
endif()
# include ncurses to binary
#set(CMAKE_REQUIRED_LIBRARIES "curses")
find_package(Curses REQUIRED)
# add the executable
add_executable(ncurses tutorial.cxx)

target_link_libraries(ncurses PUBLIC ${EXTRA_LIBS})
target_link_libraries(ncurses PUBLIC ${CURSES_LIBRARIES})

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(ncurses PUBLIC
"${PROJECT_BINARY_DIR}"                           
)
#Sinstall(TARGETS ncurses DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
        DESTINATION bin/include
    )
#install(TARGETS ncurses DESTINATION  /home/mic/Ncurses)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
DESTINATION ${PROJECT_BINARY_DIR}/bin/include
)

enable_testing()

# does the application run
add_test(NAME Runs COMMAND ncurses 25)
        
# does the usage message work?
add_test(NAME Usage COMMAND ncurses)
set_tests_properties(Usage
    PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
    )
        
# define a function to simplify adding tests
function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg}
        PROPERTIES PASS_REGULAR_EXPRESSION ${result}
        )
    endfunction(do_test)
        
# do a bunch of result based tests
do_test(ncurses 4 "4 is 2")
do_test(ncurses 9 "9 is 3")
do_test(ncurses 5 "5 is 2.236")
do_test(ncurses 7 "7 is 2.645")
do_test(ncurses 25 "25 is 5")
do_test(ncurses -25 "-25 is [-nan|nan|0]")
do_test(ncurses 0.0001 "0.0001 is 0.01")