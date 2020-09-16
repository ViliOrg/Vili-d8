project(vili_d8_tests)

file(GLOB_RECURSE VILI_D8_TESTS_HEADERS src/*.hpp)
file(GLOB_RECURSE VILI_D8_TESTS_SOURCES src/*.cpp)

add_executable(vili_d8_tests ${VILI_D8_TESTS_HEADERS} ${VILI_D8_TESTS_SOURCES})

target_include_directories(vili_d8_tests
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(vili_d8_tests catch)
target_link_libraries(vili_d8_tests vili-d8)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)