add_library(
    Api STATIC
    api.cpp
    request.cpp
)
target_include_directories(Api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../config)
