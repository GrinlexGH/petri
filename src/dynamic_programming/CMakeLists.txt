add_executable(dynamic_programming)

target_sources(dynamic_programming
    PRIVATE
    FILE_SET SOURCES FILES
        main
)

target_link_libraries(dynamic_programming PRIVATE common)

petri_configure_target(dynamic_programming VS_STARTUP)
