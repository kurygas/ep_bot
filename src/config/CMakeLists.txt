add_library(Config STATIC config.cpp)
target_include_directories(Config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
