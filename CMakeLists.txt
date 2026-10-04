cmake_minimum_required(VERSION 4.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(Petri LANGUAGES CXX C)

# Global settings
set(PETRI_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
set(PETRI_BUILD_DIR ${CMAKE_BINARY_DIR}/built/$<$<BOOL:${IS_MULTI_CONFIG}>:$<CONFIG>/>)

# CMake options
include(GenerateExportHeader)
include(CheckIPOSupported)

check_ipo_supported(RESULT LTO_AVAILABLE)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${LTO_AVAILABLE})
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_VISIBILITY_PRESET hidden)

set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_DEBUGGER_WORKING_DIRECTORY ${PETRI_ROOT_DIR})

set(IS_LANG_CCXX $<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>)
set(IS_GNU_LIKE $<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>)
set(IS_MSVC_LIKE $<OR:$<CXX_COMPILER_ID:MSVC>,$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},MSVC>>)
set(IS_LTO_ENABLED $<AND:$<NOT:$<CONFIG:Debug>>,$<BOOL:${LTO_AVAILABLE}>>)

# Disable C4251 because this project is using one runtime
# Disable C4324 because I know what alignas is doing
add_compile_options(
    "$<$<AND:${IS_LANG_CCXX},${IS_GNU_LIKE}>:-Wall;-Wextra;-Wpedantic>"
    "$<$<AND:${IS_LANG_CCXX},$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:Clang>>:-fansi-escape-codes>"
    "$<$<AND:${IS_LANG_CCXX},${IS_MSVC_LIKE}>:/utf-8;/Zc:__cplusplus;/Zc:inline;/W4;/wd4251;/wd4324>"
    "$<$<AND:${IS_LANG_CCXX},${IS_LTO_ENABLED},${IS_MSVC_LIKE}>:/Gy;/Gw>"
    "$<$<AND:${IS_LANG_CCXX},${IS_LTO_ENABLED},$<CXX_COMPILER_ID:MSVC>,$<VERSION_GREATER_EQUAL:${CMAKE_CXX_COMPILER_VERSION},19.35>>:/Zc:checkGwOdr>"
)

# Disable missing .pdb file warning
add_link_options(
    "$<$<AND:${IS_LANG_CCXX},$<CXX_COMPILER_ID:MSVC>>:/ignore:4099>"
)

add_compile_definitions(
    "$<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:DEBUG>"

    "$<$<PLATFORM_ID:Windows>:PLATFORM_WINDOWS;UNICODE;_UNICODE>"
    "$<$<PLATFORM_ID:Linux>:PLATFORM_LINUX;_XOPEN_SOURCE=700>"
    "$<$<PLATFORM_ID:Darwin>:PLATFORM_APPLE>"
    "$<$<PLATFORM_ID:Android>:PLATFORM_ANDROID>"

    "$<$<CXX_COMPILER_ID:MSVC>:COMPILER_MSVC>"
    "$<$<CXX_COMPILER_ID:GNU>:COMPILER_GCC>"
    "$<$<CXX_COMPILER_ID:Clang>:COMPILER_CLANG>"
    "$<$<CXX_COMPILER_ID:AppleClang>:COMPILER_CLANG>"

    "$<$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>:ARCH_64>"
    "$<$<EQUAL:${CMAKE_SIZEOF_VOID_P},4>:ARCH_32>"
)

# petri_target_setup_ide(<target>
#     [VS_STARTUP]
# )
#
# Organizes a target's files into IDE folders (Visual Studio, Xcode, etc.).
#
# Collects the target's SOURCES, the default HEADER_SET and the default
# SOURCE_SET, then groups them as follows:
#   - Files located under the target's source directory are grouped by their
#     directory structure under "Sources".
#   - Files located outside the target's source directory are placed under
#     "External".
#   - Files from a file set named "generated" (header or source) and
#     precompiled-header files (cmake_pch.*) are placed under "Generated".
#
# Parameters:
#   <target>                    Target to organize
#   VS_STARTUP                  If the target is an executable and the generator
#                               is Visual Studio, mark it as the default
#                               startup project
function(petri_target_setup_ide target_name)
    set(options VS_STARTUP)
    cmake_parse_arguments(ARG "${options}" "" "" ${ARGN})

    set(all_files "")
    get_target_property(legacy_sources ${target_name} SOURCES)
    if(legacy_sources)
        list(APPEND all_files ${legacy_sources})
    endif()

    get_target_property(header_files ${target_name} HEADER_SET)
    if(header_files)
        list(APPEND all_files ${header_files})
    endif()

    get_target_property(source_files ${target_name} SOURCE_SET)
    if(source_files)
        list(APPEND all_files ${source_files})
    endif()

    if(all_files)
        list(REMOVE_DUPLICATES all_files)
    endif()

    get_target_property(target_source_dir ${target_name} SOURCE_DIR)

    set(in_tree_files "")
    set(external_files "")
    foreach(file ${all_files})
        cmake_path(ABSOLUTE_PATH file BASE_DIRECTORY "${target_source_dir}" NORMALIZE OUTPUT_VARIABLE abs_file)
        cmake_path(IS_PREFIX target_source_dir "${abs_file}" NORMALIZE is_in_tree)
        if(is_in_tree)
            list(APPEND in_tree_files "${file}")
        else()
            list(APPEND external_files "${file}")
        endif()
    endforeach()

    if(in_tree_files)
        source_group(TREE ${target_source_dir} PREFIX "Sources" FILES ${in_tree_files})
    endif()

    if(external_files)
        source_group("External" FILES ${external_files})
    endif()

    get_target_property(header_sets ${target_name} HEADER_SETS)
    if("generated" IN_LIST header_sets)
        get_target_property(generated_files ${target_name} HEADER_SET_generated)
        source_group("Generated" FILES ${generated_files})
    endif()

    get_target_property(source_sets ${target_name} SOURCE_SETS)
    if("generated" IN_LIST source_sets)
        get_target_property(generated_files ${target_name} SOURCE_SET_generated)
        source_group("Generated" FILES ${generated_files})
    endif()

    source_group("Generated" REGULAR_EXPRESSION "cmake_pch.*")

    get_target_property(target_type ${target_name} TYPE)
    if(ARG_VS_STARTUP AND ("${target_type}" STREQUAL "EXECUTABLE") AND (CMAKE_GENERATOR MATCHES "Visual Studio .*"))
        set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${target_name})
    endif()
endfunction()

# petri_target_setup_artifacts(<target>
#     [RUNTIME_DESTINATION <path>]
#     [ARCHIVE_DESTINATION <path>]
#     [LIBRARY_DESTINATION <path>]
#     [RUNTIME_PLUGINS <targets>...]
# )
#
# Configures build output locations for a target.
#
# Behavior:
#   - Redirects runtime, archive, library, PDB and compile-PDB outputs into
#     PETRI_BUILD_DIR.
#   - Post-build, copies the target's runtime DLLs next to the target artifact.
#   - Post-build, copies RUNTIME_PLUGINS next to the target artifact.
#
# Parameters:
#   RUNTIME_DESTINATION         Subdirectory of build destination for runtime artifacts (default: bin)
#   ARCHIVE_DESTINATION         Subdirectory of build destination for linking artifacts (default: lib)
#   LIBRARY_DESTINATION         Subdirectory of build destination for library artifacts (default: lib)
#   RUNTIME_PLUGINS             Additional targets to copy alongside <target> artifacts
function(petri_target_setup_artifacts target_name)
    set(oneValueArgs RUNTIME_DESTINATION ARCHIVE_DESTINATION LIBRARY_DESTINATION)
    set(multiValueArgs RUNTIME_PLUGINS)
    cmake_parse_arguments(ARG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(runtime_dest "bin")
    set(archive_dest "lib")
    set(library_dest "lib")

    if(ARG_RUNTIME_DESTINATION)
        set(runtime_dest ${ARG_RUNTIME_DESTINATION})
    endif()

    if(ARG_ARCHIVE_DESTINATION)
        set(archive_dest ${ARG_ARCHIVE_DESTINATION})
    endif()

    if(ARG_LIBRARY_DESTINATION)
        set(library_dest ${ARG_LIBRARY_DESTINATION})
    endif()

    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PETRI_BUILD_DIR}${runtime_dest}"
        PDB_OUTPUT_DIRECTORY "${PETRI_BUILD_DIR}${runtime_dest}"
        ARCHIVE_OUTPUT_DIRECTORY "${PETRI_BUILD_DIR}${archive_dest}"
        COMPILE_PDB_OUTPUT_DIRECTORY "${PETRI_BUILD_DIR}${archive_dest}"
        LIBRARY_OUTPUT_DIRECTORY "${PETRI_BUILD_DIR}${library_dest}"
    )

    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            -t $<TARGET_FILE_DIR:${target_name}> $<TARGET_RUNTIME_DLLS:${target_name}>
        COMMAND_EXPAND_LISTS
    )

    if(ARG_RUNTIME_PLUGINS)
        set(runtime_artifacts "")
        foreach(plugin_target IN LISTS ARG_RUNTIME_PLUGINS)
            list(APPEND runtime_artifacts "$<TARGET_FILE:${plugin_target}>")
        endforeach()

        add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                -t $<TARGET_FILE_DIR:${target_name}> ${runtime_artifacts}
            COMMAND_EXPAND_LISTS
        )
    endif()
endfunction()

# petri_configure_target(<target>
#     [WIN32_IN_RELEASE] [VS_STARTUP]
#     [RUNTIME_DESTINATION <path>]
#     [ARCHIVE_DESTINATION <path>]
#     [LIBRARY_DESTINATION <path>]
#     [RUNTIME_PLUGINS <targets>...]
# )
#
# One-stop setup for a Skylabs target. Call it once after the target is
# created and its sources are added.
#
# Behavior:
#   1. Calls petri_target_setup_ide() to organize files into IDE folders.
#   2. Skips steps below if the target is not a static, module, shared or object
#      library or an executable.
#   3. For non-executable targets, generates an export header named
#      pt_<target>_export.h with the PT_ prefix, which also defines:
#        PT_<TARGET>_PUBLIC_INTERFACE   extern "C" + export attribute
#        PT_<TARGET>_PUBLIC_GLOBAL      extern + export attribute
#        PT_<TARGET>_PUBLIC_CLASS       export attribute
#      (<TARGET> is the uppercased target name converted to a C identifier)
#   4. On Windows for executables links comctl32 and adds win32.manifest
#   5. Calls petri_target_setup_artifacts() to configure output directories
#      and post-build copies.
#
# Parameters:
#   VS_STARTUP                  Set target as Visual Studio default startup project
#   RUNTIME_DESTINATION         Subdirectory of build destination for runtime artifacts (default: bin)
#   ARCHIVE_DESTINATION         Subdirectory of build destination for linking artifacts (default: lib)
#   LIBRARY_DESTINATION         Subdirectory of build destination for library artifacts (default: lib)
#   RUNTIME_PLUGINS             Additional targets to copy alongside <target> artifacts
function(petri_configure_target target_name)
    set(options VS_STARTUP)
    set(oneValueArgs RUNTIME_DESTINATION ARCHIVE_DESTINATION LIBRARY_DESTINATION)
    set(multiValueArgs RUNTIME_PLUGINS)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(function_args "")
    if(ARG_VS_STARTUP)
        list(APPEND function_args VS_STARTUP)
    endif()

    petri_target_setup_ide(${target_name} ${function_args})

    get_target_property(target_type ${target_name} TYPE)
    if(NOT("${target_type}" MATCHES "STATIC_LIBRARY|MODULE_LIBRARY|SHARED_LIBRARY|OBJECT_LIBRARY|EXECUTABLE"))
        return()
    endif()

    if(NOT("${target_type}" STREQUAL "EXECUTABLE"))
        string(TOUPPER "${target_name}" uppercase_target_name)
        string(MAKE_C_IDENTIFIER "${uppercase_target_name}" uppercase_target_name)
        set(export_header_content
"
#define PT_${uppercase_target_name}_PUBLIC_INTERFACE extern \"C\" PT_${uppercase_target_name}_EXPORT
#define PT_${uppercase_target_name}_PUBLIC_GLOBAL extern PT_${uppercase_target_name}_EXPORT
#define PT_${uppercase_target_name}_PUBLIC_CLASS PT_${uppercase_target_name}_EXPORT
"
        )
        generate_export_header(${target_name}
            EXPORT_FILE_NAME "pt_${target_name}_export.h"
            CUSTOM_CONTENT_FROM_VARIABLE export_header_content
            PREFIX_NAME "PT_"
        )
        unset(uppercase_target_name)
    endif ()

    if(WIN32 AND ("${target_type}" STREQUAL "EXECUTABLE"))
        target_sources(${target_name} PRIVATE ${PETRI_ROOT_DIR}/cmake/win32.manifest)
        target_link_libraries(${target_name} PRIVATE comctl32)
    endif()

    set(function_args "")
    if(ARG_RUNTIME_DESTINATION)
        list(APPEND function_args RUNTIME_DESTINATION "${ARG_RUNTIME_DESTINATION}")
    endif()

    if(ARG_ARCHIVE_DESTINATION)
        list(APPEND function_args ARCHIVE_DESTINATION "${ARG_ARCHIVE_DESTINATION}")
    endif()

    if(ARG_LIBRARY_DESTINATION)
        list(APPEND function_args LIBRARY_DESTINATION "${ARG_LIBRARY_DESTINATION}")
    endif()

    if(ARG_RUNTIME_PLUGINS)
        list(APPEND function_args RUNTIME_PLUGINS ${ARG_RUNTIME_PLUGINS})
    endif()

    petri_target_setup_artifacts(${target_name} ${function_args})
endfunction()

# Third party libraries
find_package(fmt CONFIG REQUIRED)

# Sources
add_subdirectory(src)
