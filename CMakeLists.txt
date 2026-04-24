add_library(custom 
                ScreenSettings.h
                layer/ButtonLayer.cpp
                layer/ButtonLayer.h
                layer/HvacLayer.cpp
                layer/HvacLayer.h
                layer/InfoLayer.cpp
                layer/InfoLayer.h
                layer/MapLayer.cpp
                layer/MapLayer.h
                layer/SettingsLayer.cpp
                layer/SettingsLayer.h
)

target_include_directories(custom PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_SOURCE_DIR}/src
                            ${CMAKE_SOURCE_DIR}/src/data
                            ${CMAKE_SOURCE_DIR}/vendor/raylib/src
                            ${CMAKE_SOURCE_DIR}/vendor/yaml-cpp/include
                            ${CMAKE_SOURCE_DIR}/vendor/fmt/include
                            )