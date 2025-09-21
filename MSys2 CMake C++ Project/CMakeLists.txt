cmake_minimum_required(VERSION 3.15)

# Project Name and language
project(#{PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Uncomment the following lines if you want to use libraries, eg libmosbuspp
# find_package(PkgConfig REQUIRED) 
# pkg_check_modules(LIBMOSBUSPP REQUIRED IMPORTED_TARGET libmosbuspp)

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Uncomment the following line if you want to link libraries, eg libmosbuspp
# target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::LIBMOSBUSPP)

# set(PROGRAM_PERMISSIONS_BY_ROOT
#     OWNER_WRITE OWNER_READ OWNER_EXECUTE
#     GROUP_READ GROUP_EXECUTE
#     WORLD_READ WORLD_EXECUTE SETUID)
# install(TARGETS ${PROJECT_NAME} DESTINATION bin PERMISSIONS ${PROGRAM_PERMISSIONS_BY_ROOT})
