cmake_minimum_required(VERSION 3.21.2)

project(FLAPPY_BIRD)

set(DEPS_DIR ${CMAKE_SOURCE_DIR}/build/external)

file(GLOB FLAPPY_BIRD_SOURCE_FILES src/*.cpp)
file(GLOB FLAPPY_BIRD_HEADER_FILES include/*.h)

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)

add_subdirectory(external/SDL_ttf EXCLUDE_FROM_ALL)

add_executable(FLAPPY_BIRD ${FLAPPY_BIRD_SOURCE_FILES} ${FLAPPY_BIRD_HEADER_FILES})

target_include_directories(FLAPPY_BIRD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_ttf/)

target_link_libraries(FLAPPY_BIRD PRIVATE SDL2 SDL2main SDL2_image SDL2_ttf)

add_custom_command(TARGET FLAPPY_BIRD POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DEPS_DIR}/SDL/Debug/SDL2d.dll"
                    "${DEPS_DIR}/SDL_image/Debug/SDL2_imaged.dll"
                    "${DEPS_DIR}/SDL_ttf/Debug/SDL2_ttfd.dll"
                    "${DEPS_DIR}/SDL_ttf/external/freetype/Debug/freetyped.dll"
                    $<TARGET_FILE_DIR:FLAPPY_BIRD>)

add_custom_command(TARGET FLAPPY_BIRD POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:FLAPPY_BIRD>/res)                    