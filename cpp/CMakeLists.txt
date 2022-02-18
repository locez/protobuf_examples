cmake_minimum_required(VERSION 3.7)

project(protobuf_example)

set(CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

if( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
  add_compile_options(-g)
endif()

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PROTOBUF_GENERATE_CPP_APPEND_PATH FALSE)

file(GLOB_RECURSE PROTO_FILES "${PROJECT_SOURCE_DIR}/proto/*.proto")

message("message: " ${PROTO_FILES})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

add_library(protobuf_lib ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(protobuf_lib ${Protobuf_LIBRARIES})

add_executable(read_write read_write.cpp)
target_link_libraries(read_write protobuf_lib)

add_executable(pb2json pb2json.cpp)
target_link_libraries(pb2json protobuf_lib)

install(TARGETS read_write pb2json)
