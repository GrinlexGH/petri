add_executable(vulkan)

target_sources(vulkan
    PRIVATE
    FILE_SET HEADERS FILES
        sdl.hpp
    FILE_SET SOURCES FILES
        main.cpp
        sdl.cpp
)

target_link_libraries(vulkan PRIVATE
    common
    SDL3::SDL3
    glm::glm
    Vulkan::Headers
    vk-bootstrap::vk-bootstrap
    VulkanMemoryAllocator-Hpp::VulkanMemoryAllocator-Hpp
)

petri_configure_target(vulkan VS_STARTUP)
