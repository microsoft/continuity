
## Simple wrapper around NuGet
##
## All commands run in a nuget package directory.

function(NuGet)
    set(NUGET_COMMAND nuget)
    set(NUGET_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/nuget_packages)

    file(MAKE_DIRECTORY ${NUGET_WORKING_DIRECTORY})

    list(JOIN ARGN " " NUGET_ARGS_AS_STRING)
    message(STATUS "[${NUGET_WORKING_DIRECTORY}] ${NUGET_COMMAND} ${NUGET_ARGS_AS_STRING}")
    execute_process(COMMAND ${NUGET_COMMAND} ${ARGN}
        WORKING_DIRECTORY ${NUGET_WORKING_DIRECTORY}
        RESULT_VARIABLE NUGET_RESULT
        COMMAND_ECHO STDOUT)
    if(NOT NUGET_RESULT EQUAL 0)
        message(FATAL_ERROR "NuGet failed with error: ${NUGET_RESULT}")
    endif()
endfunction()
