cmake_minimum_required(VERSION 3.13)
project(hclib VERSION 0.0.1 LANGUAGES C)

option(HCLIB_BUILD_EXAMPLES "Build library examples" ON)

add_library(hc
    include/hclib/hc_def.h
    include/hclib/hc_macros.h
    include/hclib/hc_destructor.h
    include/hclib/hc_allocator.h
    include/hclib/hc_list.h

    src/memory.h
    src/hc_list.c
)
target_include_directories(hc PUBLIC include)
set_target_properties(hc PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_compile_features(hc PUBLIC c_std_11)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(hc PRIVATE HCLIB_EXPORTING)
endif()

install(TARGETS hc
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(HC_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
