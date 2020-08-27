cmake_minimum_required(VERSION 3.13)
project(hclib VERSION 0.0.1 LANGUAGES C)

option(HC_BUILD_EXAMPLES "Build library examples"       ON)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(hclib
    include/hclib/hc_def.h
    include/hclib/hc_macros.h
    include/hclib/hc_destructor.h
    include/hclib/hc_allocator.h
    include/hclib/hc_list.h

    src/memory.h
    src/hc_list.c
)
target_include_directories(hclib PUBLIC include)
set_target_properties(hclib PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_compile_features(hclib PUBLIC c_std_11)
if(BUILD_SHARED_LIBS)
    target_compile_definitions(hclib PRIVATE HCLIB_EXPORTING)
    # target_compile_definitions(hclib PUBLIC HCLIB_DLL)
endif()

install(TARGETS hclib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(HC_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
