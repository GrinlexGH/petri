add_subdirectory(common)
add_subdirectory(sorting)
add_subdirectory(heap)
add_subdirectory(vulkan)
add_subdirectory(dynamic_programming)

if(CMAKE_CXX_STDLIB_MODULES_JSON)
    add_subdirectory(std_module)
endif()
