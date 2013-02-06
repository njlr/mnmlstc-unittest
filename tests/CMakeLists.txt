add_custom_target(check COMMAND ${CMAKE_TEST_COMMAND})

# TODO: Do a check if RTTI is disabled and remove the equivalent tests (type)
#       if it is.
add_executable(test-task-name ${TEST_SOURCE_DIR}/task/name.cpp)
add_executable(test-task-call ${TEST_SOURCE_DIR}/task/call.cpp)
add_executable(test-task-type ${TEST_SOURCE_DIR}/task/type.cpp)

target_link_libraries(test-task-name unittest)
target_link_libraries(test-task-call unittest)
target_link_libraries(test-task-type unittest)

add_test(task-name test-task-name)
add_test(task-call test-task-call)
add_test(task-type test-task-type)

add_dependencies(check test-task-name)
add_dependencies(check test-task-call)
add_dependencies(check test-task-type)
