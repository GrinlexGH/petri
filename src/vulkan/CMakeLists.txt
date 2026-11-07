add_executable(vulkan)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h" "*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.c" "*.cc" "*.cpp")

if(headers)
    target_sources(vulkan
        PRIVATE
            FILE_SET HEADERS
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
            FILES ${headers}
    )
endif()

if(sources)
    target_sources(vulkan
        PRIVATE
            FILE_SET SOURCES
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
            FILES ${sources}
    )
endif()

target_link_libraries(vulkan PRIVATE
    SDL3::SDL3
    fmt::fmt
    glm::glm
    Vulkan::Headers
    vk-bootstrap::vk-bootstrap
    VulkanMemoryAllocator-Hpp::VulkanMemoryAllocator-Hpp
)

petri_configure_target(vulkan VS_STARTUP)
