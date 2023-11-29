cmake_minimum_required(VERSION 3.18.4)

# Setting a variable to use for both the project name and the resulting binary executable
set(REPO lle)
project(${REPO})
set(PROJECT_NAME ${REPO})


# Set the C standard to C99
set(CMAKE_C_STANDARD 99)

# Compiler  pre-processing flags
set(CPP_FLAGS 
        "-Wall" 
        "-Wextra" 
        "-pedantic" 
        "-Wno-builtin-declaration-mismatch"
)
# Set anti-lib flags
set(NOLIB 
        -static-libgcc 
        -static-libstdc++ 
        -static-libasan 
        -nostartfiles 
        -nostdlib
)

# Add the src directory to the include path
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add all the source files in the src directory to the project
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

# Create the executable from the source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/driver.c ${SOURCES})


# Set the output directory to the build/bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        COMPILE_FLAGS ${CPP_FLAGS} ${NOLIB}
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin
        )

# Set the object directory to the build/obj directory
set_property(
        TARGET ${PROJECT_NAME}
        PROPERTY
        CMAKE_OBJECT_PATH_PREFIX ${PROJECT_SOURCE_DIR}/build/obj/
)

# Set link options
target_link_options(${PROJECT_NAME} PRIVATE ${CPP_FLAGS} ${NOLIB} -g)
# Set compiler flags for the target
target_compile_options(${PROJECT_NAME} PRIVATE ${CPP_FLAGS} ${NOLIB} -g)

# Set the cmake binary directory to the build/cmake directory
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build/cmake)

# Add the build/cmake directory to the include path
include_directories(${PROJECT_SOURCE_DIR}/build/cmake)


# Add any other dependencies here, such as libraries or additional build options

#13/44