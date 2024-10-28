cmake_minimum_required(VERSION 3.28)
project(VMTranslator_C C)

set(CMAKE_C_STANDARD 23)

add_executable(VMTranslator_C main.c
        parser.c
        parser.h
        codewriter.c
        codewriter.h)
