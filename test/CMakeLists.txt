set(TARGET_NAME cutils-test)

file(GLOB_RECURSE SOURCES *.c)

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX)

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME} PRIVATE cutils)
