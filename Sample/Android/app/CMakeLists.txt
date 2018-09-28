cmake_minimum_required(VERSION 3.4.1)

#添加源码公共库的编译
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode out)

add_library( native-lib
             SHARED
             src/main/cpp/native-lib.cpp)


find_library( log-lib
              log )

target_include_directories(native-lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                           native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode>
   )

target_link_libraries( native-lib
                       SourceCode
                       ${log-lib} )