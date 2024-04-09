include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "*.cpp")

add_library(skiplist ${SOURCES})

# 确保你的主CMakeLists.txt知道这个库的位置
target_include_directories(skiplist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
