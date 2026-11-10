add_library(common STATIC)

target_sources(common
    PUBLIC
    FILE_SET HEADERS FILES
        petri/logging.hpp
    PRIVATE
    FILE_SET SOURCES FILES
        logging.cpp
)

target_link_libraries(common PUBLIC fmt::fmt)

petri_configure_target(common)
