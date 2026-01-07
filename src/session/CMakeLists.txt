project(session)

add_library(${PROJECT_NAME} session.h session.cpp)

find_package(Boost REQUIRED COMPONENTS system)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} Boost::system storage)