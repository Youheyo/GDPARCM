cmake_minimum_required(VERSION 3.16)
project(GDPARCM LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES "src/*.cpp")

add_executable(
    GDPARCM 
    ${SOURCES}
    )
target_include_directories(GDPARCM PRIVATE ${PROJECT_SOURCE_DIR} )
target_link_libraries(GDPARCM PRIVATE sfml-graphics sfml-window sfml-system )
target_compile_features(GDPARCM PRIVATE cxx_std_20)

file(COPY ${CMAKE_SOURCE_DIR}/Media DESTINATION ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    set_target_properties(GDPARCM PROPERTIES WIN32_EXECUTABLE TRUE)

    add_custom_command(
        TARGET GDPARCM
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:GDPARCM>
        VERBATIM)

endif()

install(TARGETS GDPARCM)
