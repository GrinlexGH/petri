add_executable(dynamic_programming)

target_sources(dynamic_programming
    PRIVATE
    FILE_SET SOURCES FILES
        main.cpp
        task1.cpp
        task2.cpp
        task5.cpp
        task5s.cpp
)

target_link_libraries(dynamic_programming PRIVATE common)

petri_configure_target(dynamic_programming VS_STARTUP)
