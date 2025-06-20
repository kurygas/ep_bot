add_library(
    Bot STATIC
    bot.cpp
    command_handler.cpp
    register_handler.cpp
    create_group_handler.cpp
    add_to_group_handler.cpp
)
target_include_directories(Bot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Bot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../config)
target_include_directories(Bot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../api)
