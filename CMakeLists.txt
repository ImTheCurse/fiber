cmake_minimum_required(VERSION 3.16)
project(fiber LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(src/Graphics , src/textDocument,src/Handlers, src/Events)
add_executable(fiber 
src/main.cpp
src/textDocument/doc.cpp
src/Graphics/editorView.hpp
src/textDocument/doc.hpp
src/Graphics/editorView.cpp
src/Events/editorEvents.hpp
src/Events/editorEvents.cpp
src/TextCursor/TextCursor.cpp
src/TextCursor/TextCursor.hpp
src/Handlers/EventHandler.cpp
src/Handlers/EventHandler.hpp
src/Events/Selection.cpp
src/Events/Selection.hpp
src/util.cpp
src/util.hpp

)
target_link_libraries(fiber PRIVATE sfml-graphics)
target_compile_features(fiber PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET fiber
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:fiber>
        VERBATIM)
endif()

install(TARGETS fiber)
