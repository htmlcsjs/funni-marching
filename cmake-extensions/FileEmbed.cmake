# add resources

function(add_resources return_var)
    set(return_list)
    foreach(infile ${ARGN})
        file(RELATIVE_PATH src_path ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${infile})
        set(out_path "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}-resources.dir/${infile}.o")
        cmake_path(GET out_path PARENT_PATH out_path_dir)
        file(MAKE_DIRECTORY ${out_path_dir})
        add_custom_command(OUTPUT ${out_path}
            COMMAND ld -r -b binary -o ${out_path} ${src_path}
            DEPENDS ${infile}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Building resource object ${out_path}"
            VERBATIM
        )
        list(APPEND return_list ${out_path})
    endforeach(infile ${ARGN})
    set(${return_var} "${return_list}" PARENT_SCOPE)
endfunction()

