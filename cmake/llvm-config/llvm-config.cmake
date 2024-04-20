find_package(LLVM REQUIRED CONFIG)

function(execute_llvm_config OUTPUT)
  set(LLVM_CONFIG "${LLVM_TOOLS_BINARY_DIR}/llvm-config")
  set(LLVM_CONFIG_ARGS ${ARGN})
  execute_process(
    COMMAND ${LLVM_CONFIG} ${LLVM_CONFIG_ARGS}
    OUTPUT_VARIABLE ${OUTPUT}
    RESULT_VARIABLE LLVM_CONFIG_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(LLVM_CONFIG_RESULT)
    list(JOIN ARGN " " LLVM_CONFIG_ARGS_PRETTY)
    message(FATAL_ERROR
            "`llvm-config ${LLVM_CONFIG_ARGS_PRETTY}` failed with status "
            "${LLVM_CONFIG_RESULT}")
  endif()
  set(${OUTPUT} "${${OUTPUT}}" PARENT_SCOPE)
endfunction()

function(my_llvm_config TARGET)
  set(LLVM_CONFIG_COMPONENTS ${ARGN})

  target_include_directories(${TARGET} PUBLIC ${LLVM_INCLUDE_DIRS})

  separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
  target_compile_definitions(${TARGET} PUBLIC ${LLVM_DEFINITIONS_LIST})

  execute_llvm_config(LLVM_LDFLAGS --ldflags)
  separate_arguments(LLVM_LDFLAGS_LIST NATIVE_COMMAND ${LLVM_LDFLAGS})
  if(BUILD_SHARED_LIBS)
    set(LLVM_CONFIG_LINK_FLAG "--link-shared")
  else()
    set(LLVM_CONFIG_LINK_FLAG "--link-static")
  endif()
  execute_llvm_config(LLVM_LIBS
                      ${LLVM_CONFIG_LINK_FLAG} --libs
                      ${LLVM_CONFIG_COMPONENTS})
  separate_arguments(LLVM_LIBS_LIST NATIVE_COMMAND ${LLVM_LIBS})
  execute_llvm_config(LLVM_SYSTEM_LIBS
                      ${LLVM_CONFIG_LINK_FLAG} --system-libs
                      ${LLVM_CONFIG_COMPONENTS})
  separate_arguments(LLVM_SYSTEM_LIBS_LIST NATIVE_COMMAND ${LLVM_SYSTEM_LIBS})

  get_target_property(TARGET_TYPE ${TARGET} TYPE)
  if (TARGET_TYPE STREQUAL "STATIC_LIBRARY")
    target_link_options(${TARGET} INTERFACE ${LLVM_LDFLAGS_LIST})
    target_link_libraries(${TARGET} INTERFACE ${LLVM_LIBS_LIST})
    target_link_libraries(${TARGET} INTERFACE ${LLVM_SYSTEM_LIBS_LIST})
  elseif(TARGET_TYPE STREQUAL "MODULE_LIBRARY" OR
         TARGET_TYPE STREQUAL "SHARED_LIBRARY" OR
         TARGET_TYPE STREQUAL "EXECUTABLE")
    target_link_options(${TARGET} PRIVATE ${LLVM_LDFLAGS_LIST})
    target_link_libraries(${TARGET} PRIVATE ${LLVM_LIBS_LIST})
    target_link_libraries(${TARGET} PRIVATE ${LLVM_SYSTEM_LIBS_LIST})
  else()
    target_link_options(${TARGET} ${LLVM_LDFLAGS_LIST})
    target_link_libraries(${TARGET} ${LLVM_LIBS_LIST})
    target_link_libraries(${TARGET} ${LLVM_SYSTEM_LIBS_LIST})
  endif()
endfunction()
