#设置编译的c++版本
add_definitions(-std=c++11)

#源码路径
file(GLOB srcCode "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Application/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Core/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Graphics/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Graphics/gl/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Input/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Math/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Metrial/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Resource/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Scence/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/SkySnow2D/*.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Utils/*.cpp"
			      "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Application/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Core/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Graphics/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Graphics/gl/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Input/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Math/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Metrial/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Resource/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Scence/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/SkySnow2D/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Utils/*.c")

#源码编译 SHARED
add_library(SourceCode SHARED
            ${srcCode})

#头文件路径
target_include_directories( SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Application
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Core
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Graphics
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Graphics/gl
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Input
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Math
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Metrial
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Resource
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/Scence
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SkySnow/SkySnow2D
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm/detail
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm/gtc
                            SourceCode  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm/gtx
	                       )

target_link_libraries( SourceCode
                       GLESv2)