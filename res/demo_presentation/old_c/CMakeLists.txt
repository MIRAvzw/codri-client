#
# Configure dependancies
#

# Use PkgConfig to find them
find_package(PkgConfig)

# GTK+
pkg_check_modules(GTK gtk+-2.0)
include_directories(${GTK_INCLUDE_DIRS})

# Webkit
pkg_check_modules(WEBKIT webkit-1.0)
include_directories(${WEBKIT_INCLUDE_DIRS})


#
# Build libraries
#

# Browser
ADD_LIBRARY(browser browser.c browser.h)
TARGET_LINK_LIBRARIES(browser ${GTK_LIBRARIES})
TARGET_LINK_LIBRARIES(browser ${WEBKIT_LIBRARIES})

#
# Build executables
#

# Main
ADD_EXECUTABLE(main main.c) 
TARGET_LINK_LIBRARIES(main browser)

