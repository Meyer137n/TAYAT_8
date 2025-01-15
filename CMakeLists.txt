# Укажите минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Укажите имя проекта и стандарт C++
project(SemanticTree VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Укажите путь к исходным и заголовочным файлам
include_directories(include)

# Укажите файлы исходного кода
set(SOURCES
    src/main.cpp
    src/Diagram.cpp
    src/Scaner.cpp
    src/Tree.cpp
)

# Создайте исполняемый файл
add_executable(SemanticTree ${SOURCES})

# (Дополнительно) Укажите зависимости или дополнительные опции
# Например: target_link_libraries(MyProject <library>)
