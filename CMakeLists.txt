cmake_minimum_required(VERSION 3.10)

project(TPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Agregado "Audio" a los componentes requeridos de SFML
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

# Todos los .cpp
file(GLOB SRC_FILES "*.cpp")

add_executable(game ${SRC_FILES})

# 2. Agregado "SFML::Audio" a las librerías para linkear
target_link_libraries(game 
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

# 🔥 IMPORTANTE: copiar assets al build
file(COPY imagen DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Tiles DESTINATION ${CMAKE_BINARY_DIR})

# si el bmp está suelto en la raíz
file(COPY yo.bmp DESTINATION ${CMAKE_BINARY_DIR})

# mapas o txt
file(COPY testmap.txt DESTINATION ${CMAKE_BINARY_DIR})