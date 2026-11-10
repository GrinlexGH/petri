add_executable(sorting)

target_sources(sorting
    PRIVATE
    FILE_SET HEADERS FILES
        sort.hpp
    FILE_SET SOURCES FILES
        main.cpp
        counting_sort.cpp
        insertion_sort.cpp
        merge_sort.cpp
        quick_sort.cpp
        radix_sort.cpp
        selection_sort.cpp
        quick_select.cpp
)

target_link_libraries(sorting PRIVATE common)

petri_configure_target(sorting VS_STARTUP)
