#
# Configure dependancies
#

# Use PkgConfig to find them
find_package(PkgConfig)

# GTKmm
pkg_check_modules(GTK gtkmm-2.4)
include_directories(${GTK_INCLUDE_DIRS})

# WebKitmm
pkg_check_modules(WEBKIT webkitmm-1.0)
include_directories(${WEBKIT_INCLUDE_DIRS})


#
# Build libraries
#

# Browser
ADD_LIBRARY(browser browser.cpp browser.hpp)
TARGET_LINK_LIBRARIES(browser ${GTK_LIBRARIES})
TARGET_LINK_LIBRARIES(browser ${WEBKIT_LIBRARIES})

#
# Build executables
#

# Main
ADD_EXECUTABLE(main main.cpp) 
TARGET_LINK_LIBRARIES(main browser)

