add_subdirectory(gui)
add_subdirectory(game)
# add_subdirectory(solver)
# add_subdirectory(common)

# # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
# find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
# # 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
# find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

add_executable(main main.cc)
find_package(SDL2 REQUIRED)

# if(TARGET SDL2::SDL2main)
#     # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
#     target_link_libraries(main PRIVATE SDL2::SDL2main)
# endif()

# # Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
# target_link_libraries(main PRIVATE SDL2::SDL2)

target_link_libraries(main PUBLIC  ${SDL2_LIBRARIES})
include_directories(${SDL2_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src/common/)

# set_target_properties(common_lib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(main PRIVATE ${PROJECT_NAME}_gui ${PROJECT_NAME}_game ) # ${PROJECT_NAME}_solver


