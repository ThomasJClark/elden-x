cmake_minimum_required(VERSION 3.28.1)

set(CMAKE_GENERATOR_PLATFORM x64)

project(elden-x
  VERSION   "0.0.0"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

option(ER_WITH_HOOKS "Support hooking functions using MinHook" ON)

include(FetchContent)

if (ER_WITH_HOOKS)
  FetchContent_Declare(minhook
    GIT_REPOSITORY        https://github.com/TsudaKageyu/minhook.git
    GIT_TAG               f5485b8454544c2f034c78f8f127c1d03dea3636)
endif()

FetchContent_Declare(pattern16
  GIT_REPOSITORY        https://github.com/Dasaav-dsv/Pattern16.git
  GIT_TAG               728eac543cee7e7bf6fda445d7db06e3dc8a61d0
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         "")

set(SPDLOG_DISABLE_DEFAULT_LOGGER ON)
set(SPDLOG_USE_STD_FORMAT ON)
FetchContent_Declare(spdlog
  GIT_REPOSITORY        https://github.com/gabime/spdlog.git
  GIT_TAG               v1.13.0)

# Set iterator debug level to 0 for ELDEN RING ABI compatibility
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

if (ER_WITH_HOOKS)
  FetchContent_MakeAvailable(minhook)
endif()

FetchContent_MakeAvailable(pattern16 spdlog)

add_library(pattern16 INTERFACE)
target_include_directories(pattern16 INTERFACE ${pattern16_SOURCE_DIR}/include)

add_library(elden-x STATIC
  src/elden-x/messages.cpp
  src/elden-x/gamedata/game_data_man.cpp
  src/elden-x/game_man.cpp
  src/elden-x/graphics.cpp
  src/elden-x/task.cpp
  src/elden-x/utils/modutils.cpp
  src/elden-x/params/solo_param_repository.cpp
  src/elden-x/singletons.cpp)

set_target_properties(elden-x PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(elden-x PUBLIC include)

if (ER_WITH_HOOKS)
  target_link_libraries(elden-x minhook)
  target_compile_definitions(elden-x PRIVATE ER_WITH_HOOKS)
endif()

target_link_libraries(elden-x pattern16 spdlog)
