# Use the LLVM/Clang compiler
#SET(CMAKE_C_COMPILER "clang")
#SET(CMAKE_CXX_COMPILER "clang++")

# Configure the project
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(KIOSK_APP)

# Enable warnings
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add an "profile" build type
SET(CMAKE_CXX_FLAGS_PROFILE "-pg" CACHE STRING
    "Flags used by the C++ compiler during profiled builds."
    FORCE)
SET(CMAKE_C_FLAGS_PROFILE "-pg" CACHE STRING
    "Flags used by the C compiler during profiled builds."
    FORCE)
MARK_AS_ADVANCED(
    CMAKE_CXX_FLAGS_PROFILE
    CMAKE_C_FLAGS_PROFILE)

# Type of build ("debug", "release" or "profile")
SET(CMAKE_BUILD_TYPE debug)

# Add individual subdirectories
ADD_SUBDIRECTORY(src)

# Copy the HTML code as well
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/html
	${CMAKE_BINARY_DIR}/html
)
