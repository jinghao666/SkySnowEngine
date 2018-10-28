cmake_minimum_required(VERSION 3.4.1)

#添加源码公共库的编译
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode out)
set(SkySnowAndroid "${CMAKE_CURRENT_SOURCE_DIR}/../../../SourceCode")
add_library( SkySnow_Lib
             SHARED
             src/main/cpp/SkySnowJni.cpp)

target_include_directories( SkySnow_Lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Application/>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Core>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Graphics>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Graphics/gl>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Input>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Math>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Metrial>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Particle>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Resource>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Sample>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/Scence>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/SkySnow/SkySnow2D>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/ThirdParty/glm>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/ThirdParty/glm/detail>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/ThirdParty/glm/gtc>
                            SkySnow_Lib PRIVATE $<BUILD_INTERFACE:${SkySnowAndroid}/ThirdParty/glm/gtx>
                           )

target_link_libraries( SkySnow_Lib
                       SourceCode
                       GLESv2
                       log
                       )