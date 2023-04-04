cmake_minimum_required(VERSION 3.14)
project(sem)

set(CMAKE_CXX_STANDARD 14)

#    все эти флаги есть в тестирующей системе
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror") #это все warningи, [-pedantic ~ говорит про стандарт], [-Werror ~ если qrning, то ошибка компиляции]


add_executable(sem main.cpp)