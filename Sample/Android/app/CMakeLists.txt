cmake_minimum_required(VERSION 3.4.1)

#添加源码公共库的编译
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode out)
set(SkySnowAndroid "${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode")
add_library( native-lib
             SHARED
             src/main/cpp/native-lib.cpp)


find_library( log-lib
              log )

target_include_directories( native-lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Application>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Core>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Graphics>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Graphics/gl>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Input>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Math>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Metrial>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Resource>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Scence>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/SkySnow2D>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/ThirdParty/glm>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/ThirdParty/glm/detail>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/ThirdParty/glm/gtc>
                            native-lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/ThirdParty/glm/gtx>
                           )

target_link_libraries( native-lib
                       SourceCode
                       GLESv2
                       ${log-lib} )