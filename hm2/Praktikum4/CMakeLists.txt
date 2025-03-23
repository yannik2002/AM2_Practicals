cmake_minimum_required(VERSION 3.24)
project(praktikum)

set(CMAKE_CXX_STANDARD 17)

add_executable(praktikum1 main.cpp CMyVektor.cpp CMyVektor.h CMyMatrix.h CMyMatrix.cpp C_DGLSolver.cpp C_DGLSolver.h CKomplex.h CKomplex.cpp)
