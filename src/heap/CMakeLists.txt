add_executable(heap)

target_sources(heap
    PRIVATE
    FILE_SET SOURCES FILES
        main.cpp
        task1.cpp
        task2.cpp
        task3.cpp
        task4.cpp
        task5.cpp
)

target_link_libraries(heap PRIVATE common)

petri_configure_target(heap VS_STARTUP)
