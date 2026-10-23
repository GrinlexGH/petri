add_executable(heap)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h" "*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.c" "*.cc" "*.cpp")

if(headers)
    target_sources(heap
        PRIVATE
            FILE_SET HEADERS
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
            FILES ${headers}
    )
endif()

if(sources)
    target_sources(heap
        PRIVATE
            FILE_SET SOURCES
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
            FILES ${sources}
    )
endif()

target_link_libraries(heap PRIVATE fmt::fmt)

petri_configure_target(heap VS_STARTUP)
