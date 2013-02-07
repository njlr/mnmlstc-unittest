add_custom_target(check COMMAND ${CMAKE_TEST_COMMAND})

# TODO: Do a check if RTTI is disabled and remove the equivalent tests (type)
#       if it is.
add_executable(test-task-name ${TEST_SOURCE_DIR}/task/name.cpp)
add_executable(test-task-call ${TEST_SOURCE_DIR}/task/call.cpp)
add_executable(test-task-type ${TEST_SOURCE_DIR}/task/type.cpp)

add_executable(test-skip-default ${TEST_SOURCE_DIR}/skip/default.cpp)
add_executable(test-skip-unless ${TEST_SOURCE_DIR}/skip/unless.cpp)
add_executable(test-skip-if ${TEST_SOURCE_DIR}/skip/if.cpp)

add_executable(test-safe-iter ${TEST_SOURCE_DIR}/safe/iter.cpp)
add_executable(test-safe-size ${TEST_SOURCE_DIR}/safe/size.cpp)

target_link_libraries(test-task-name unittest)
target_link_libraries(test-task-call unittest)
target_link_libraries(test-task-type unittest)

target_link_libraries(test-skip-default unittest)
target_link_libraries(test-skip-unless unittest)
target_link_libraries(test-skip-if unittest)

target_link_libraries(test-safe-size unittest)
target_link_libraries(test-safe-iter unittest)

add_test(task-name test-task-name)
add_test(task-call test-task-call)
add_test(task-type test-task-type)

add_test(skip-default test-skip-default)
add_test(skip-unless test-skip-unless)
add_test(skip-if test-skip-if)

add_test(safe-size test-safe-size)
add_test(safe-iter test-safe-iter)

add_dependencies(check test-task-name)
add_dependencies(check test-task-call)
add_dependencies(check test-task-type)

add_dependencies(check test-skip-default)
add_dependencies(check test-skip-unless)
add_dependencies(check test-skip-if)

add_dependencies(check test-safe-size)
add_dependencies(check test-safe-iter)
