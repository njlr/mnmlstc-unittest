add_custom_target(check COMMAND ${CMAKE_TEST_COMMAND})

# TODO: Do a check if RTTI is disabled and remove the equivalent tests (type)
#       if it is.

#------------------------------------------------------------------------------
# Executable Section
#------------------------------------------------------------------------------
add_executable(test-task-name ${TEST_SOURCE_DIR}/task/name.cpp)
add_executable(test-task-call ${TEST_SOURCE_DIR}/task/call.cpp)
add_executable(test-task-type ${TEST_SOURCE_DIR}/task/type.cpp)

add_executable(test-skip-default ${TEST_SOURCE_DIR}/skip/default.cpp)
add_executable(test-skip-unless ${TEST_SOURCE_DIR}/skip/unless.cpp)
add_executable(test-skip-if ${TEST_SOURCE_DIR}/skip/if.cpp)

add_executable(test-safe-iter ${TEST_SOURCE_DIR}/safe/iter.cpp)
add_executable(test-safe-size ${TEST_SOURCE_DIR}/safe/size.cpp)

add_executable(test-test-name ${TEST_SOURCE_DIR}/test/name.cpp)
add_executable(test-test-run ${TEST_SOURCE_DIR}/test/run.cpp)

add_executable(test-utility-any-of ${TEST_SOURCE_DIR}/utility/any-of.cpp)
add_executable(test-utility-all-of ${TEST_SOURCE_DIR}/utility/all-of.cpp)

add_executable(test-identity-crisis ${TEST_SOURCE_DIR}/identity/crisis.cpp)
add_executable(test-identity-is-not ${TEST_SOURCE_DIR}/identity/is-not.cpp)
add_executable(test-identity-fail ${TEST_SOURCE_DIR}/identity/fail.cpp)
add_executable(test-identity-is ${TEST_SOURCE_DIR}/identity/is.cpp)

#------------------------------------------------------------------------------
# Link Section
#------------------------------------------------------------------------------
target_link_libraries(test-task-name unittest)
target_link_libraries(test-task-call unittest)
target_link_libraries(test-task-type unittest)

target_link_libraries(test-skip-default unittest)
target_link_libraries(test-skip-unless unittest)
target_link_libraries(test-skip-if unittest)

target_link_libraries(test-safe-size unittest)
target_link_libraries(test-safe-iter unittest)

target_link_libraries(test-test-name unittest)
target_link_libraries(test-test-run unittest)

target_link_libraries(test-utility-any-of unittest)
target_link_libraries(test-utility-all-of unittest)

target_link_libraries(test-identity-crisis unittest)
target_link_libraries(test-identity-is-not unittest)
target_link_libraries(test-identity-fail unittest)
target_link_libraries(test-identity-is unittest)

#------------------------------------------------------------------------------
# Test Section
#------------------------------------------------------------------------------
add_test(task-name test-task-name)
add_test(task-call test-task-call)
add_test(task-type test-task-type)

add_test(skip-default test-skip-default)
add_test(skip-unless test-skip-unless)
add_test(skip-if test-skip-if)

add_test(safe-size test-safe-size)
add_test(safe-iter test-safe-iter)

add_test(test-name test-test-name)
add_test(test-run test-test-run)

add_test(util-any-of test-utility-any-of)
add_test(util-all-of test-utility-all-of)

add_test(self-crisis test-identity-crisis)
add_test(self-is-not test-identity-is-not)
add_test(self-fail test-identity-fail)
add_test(self-is test-identity-is)

#------------------------------------------------------------------------------
# Dependency Section
#------------------------------------------------------------------------------
add_dependencies(check test-task-name)
add_dependencies(check test-task-call)
add_dependencies(check test-task-type)

add_dependencies(check test-skip-default)
add_dependencies(check test-skip-unless)
add_dependencies(check test-skip-if)

add_dependencies(check test-safe-size)
add_dependencies(check test-safe-iter)

add_dependencies(check test-test-name)
add_dependencies(check test-test-run)

add_dependencies(check test-utility-any-of)
add_dependencies(check test-utility-all-of)

add_dependencies(check test-identity-crisis)
add_dependencies(check test-identity-is-not)
add_dependencies(check test-identity-fail)
add_dependencies(check test-identity-is)
