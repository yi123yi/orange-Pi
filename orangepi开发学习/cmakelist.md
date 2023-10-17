## Lidar L1

```cmake
cmake_minimum_required(VERSION 3.0)
```
这一行指定了项目所需的最低 CMake 版本。

```cmake
project(unitree_lidar_sdk)
```
这一行设置了项目的名称。

```cmake
set(CMAKE_BUILD_TYPE "Release")
```
这一行设置了编译的类型，这里是 Release。

```cmake
set(CMAKE_CXX_FLAGS "-std=c++14")
```
这一行设置了 C++ 编译标准，这里是 C++14。

```cmake
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -DNDEBUG") 
```
这两行设置了编译调试版本和发布版本的编译标志。

```cmake
include_directories(include)
```
这一行用于添加 include 目录，以便编译器能够找到头文件。

```cmake
link_directories(lib/${CMAKE_SYSTEM_PROCESSOR})
```
这一行用于添加链接库的目录。

```cmake
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${CMAKE_SYSTEM_PROCESSOR})
```
这两行设置了可执行文件输出路径和静态库输出路径。

```cmake
add_executable(example_lidar
  examples/example_lidar.cpp
)
```
这一行添加了一个可执行文件 `example_lidar`，并指定了源文件 `examples/example_lidar.cpp`。

```cmake
target_link_libraries(example_lidar  libunitree_lidar_sdk.a )
```
这一行指定了链接 `example_lidar` 时所需的库，这里是 `libunitree_lidar_sdk.a`。

