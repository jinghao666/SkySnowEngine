cmake_minimum_required(VERSION 3.4.1)

#添加源码公共库的编译
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode out)

add_library( native-lib
             SHARED
             src/main/cpp/native-lib.cpp)


find_library( log-lib
              log )

target_include_directories( native-lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Application>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Core>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Graphics>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Graphics/gl>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Input>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Math>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Metrial>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Resource>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/Scence>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/SkySnow/SkySnow2D>
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/ThirdParty/glm
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/ThirdParty/glm/detail
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/ThirdParty/glm/gtc
                            native-lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode/ThirdParty/glm/gtx
                           )

target_link_libraries( native-lib
                       SourceCode
                       ${log-lib} )