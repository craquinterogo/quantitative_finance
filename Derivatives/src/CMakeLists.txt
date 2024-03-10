cmake_minimum_required(VERSION 3.28.3)
project(options VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

add_executable(${PROJECT_NAME} Options.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

install(TARGETS options DESTINATION bin)