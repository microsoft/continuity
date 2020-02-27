include(FetchContent)

macro(FetchContent_MakeAvailable2 NAME)
    FetchContent_GetProperties(${NAME})
    if(NOT ${NAME}_POPULATED)
        message(STATUS "Downloading ${NAME}...")
        FetchContent_Populate(${NAME})
        add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
    endif()

    message(VERBOSE "   ${NAME}_SOURCE_DIR=${${NAME}_SOURCE_DIR}")
    message(VERBOSE "   ${NAME}_BINARY_DIR=${${NAME}_BINARY_DIR}")
endmacro()
