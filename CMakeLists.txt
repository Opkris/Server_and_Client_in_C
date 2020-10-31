cmake_minimum_required(VERSION 3.17)
project(les12exe2 C)

set(CMAKE_C_STANDARD 11)

add_executable(les12exe2 client/main.c client/client.c server/main.c server/server.c)