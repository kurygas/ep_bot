cmake_minimum_required(VERSION 3.10.2)
project(ep_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CURL)
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_subdirectory(src)
add_executable(ep_bot main.cpp)

target_link_libraries(
    ep_bot PUBLIC
    Bot
    Api
    Config
    /home/kuryga/tgbot-cpp/libTgBot.a
    cpr::cpr
    nlohmann_json::nlohmann_json
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CURL_LIBRARIES}
)
