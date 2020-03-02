
function(NuGet)
    set(NUGET_COMMAND nuget)

    list(JOIN ARGN " " NUGET_ARGS_AS_STRING)
    message(STATUS "Executing: ${NUGET_COMMAND} ${NUGET_ARGS_AS_STRING}")

    execute_process(COMMAND ${NUGET_COMMAND} ${ARGN} RESULT_VARIABLE NUGET_RESULT)
    if(NOT NUGET_RESULT EQUAL 0)
        message(FATAL_ERROR "NuGet failed with error: ${NUGET_RESULT}")
    endif()
endfunction()
