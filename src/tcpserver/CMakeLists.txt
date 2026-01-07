project(tcpserver)

add_library(${PROJECT_NAME} tcpserver.h tcpserver.cpp)

find_package(Boost REQUIRED COMPONENTS system)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} Boost::system storage session)