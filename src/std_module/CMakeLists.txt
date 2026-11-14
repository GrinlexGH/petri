add_executable(std_module)

target_sources(std_module
    PRIVATE
    FILE_SET SOURCES FILES
        main.cpp
)

target_link_libraries(std_module PRIVATE common)
set_target_properties(std_module PROPERTIES CXX_SCAN_FOR_MODULES ON)

petri_configure_target(std_module VS_STARTUP)
