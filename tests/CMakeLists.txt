add_custom_target(check COMMAND ${CMAKE_TEST_COMMAND})

# TODO: Do a check if RTTI is disabled and remove the equivalent tests (type)
#       if it is.

#------------------------------------------------------------------------------
# Set Variables
#------------------------------------------------------------------------------
set(TASK_SOURCE_DIR "${TEST_SOURCE_DIR}/task")
set(SKIP_SOURCE_DIR "${TEST_SOURCE_DIR}/skip")
set(SAFE_SOURCE_DIR "${TEST_SOURCE_DIR}/safe")
set(CASE_SOURCE_DIR "${TEST_SOURCE_DIR}/case")
set(UTIL_SOURCE_DIR "${TEST_SOURCE_DIR}/util")
set(SELF_SOURCE_DIR "${TEST_SOURCE_DIR}/self")
set(RUN_SOURCE_DIR "${TEST_SOURCE_DIR}/run")

#------------------------------------------------------------------------------
# Executable Section
#------------------------------------------------------------------------------
add_executable(test-task-name ${TASK_SOURCE_DIR}/name.cpp)
add_executable(test-task-call ${TASK_SOURCE_DIR}/call.cpp)
add_executable(test-task-type ${TASK_SOURCE_DIR}/type.cpp)

add_executable(test-skip-default ${SKIP_SOURCE_DIR}/default.cpp)
add_executable(test-skip-unless ${SKIP_SOURCE_DIR}/unless.cpp)
add_executable(test-skip-if ${SKIP_SOURCE_DIR}/if.cpp)

add_executable(test-safe-iter ${SAFE_SOURCE_DIR}/iter.cpp)
add_executable(test-safe-size ${SAFE_SOURCE_DIR}/size.cpp)

add_executable(test-case-name ${CASE_SOURCE_DIR}/name.cpp)
add_executable(test-case-run ${CASE_SOURCE_DIR}/run.cpp)

add_executable(test-util-any-of ${UTIL_SOURCE_DIR}/any-of.cpp)
add_executable(test-util-all-of ${UTIL_SOURCE_DIR}/all-of.cpp)
add_executable(test-util-repr ${UTIL_SOURCE_DIR}/repr.cpp)

add_executable(test-self-greater-equal ${SELF_SOURCE_DIR}/greater-equal.cpp)
add_executable(test-self-almost-equal ${SELF_SOURCE_DIR}/almost-equal.cpp)
add_executable(test-self-is-not-null ${SELF_SOURCE_DIR}/is-not-null.cpp)
add_executable(test-self-less-equal ${SELF_SOURCE_DIR}/less-equal.cpp)
add_executable(test-self-not-equal ${SELF_SOURCE_DIR}/not-equal.cpp)
add_executable(test-self-greater ${SELF_SOURCE_DIR}/greater.cpp)
add_executable(test-self-is-null ${SELF_SOURCE_DIR}/is-null.cpp)
add_executable(test-self-is-not ${SELF_SOURCE_DIR}/is-not.cpp)
add_executable(test-self-throws ${SELF_SOURCE_DIR}/throws.cpp)
add_executable(test-self-equal ${SELF_SOURCE_DIR}/equal.cpp)
add_executable(test-self-false ${SELF_SOURCE_DIR}/false.cpp)
add_executable(test-self-true ${SELF_SOURCE_DIR}/true.cpp)
add_executable(test-self-fail ${SELF_SOURCE_DIR}/fail.cpp)
add_executable(test-self-less ${SELF_SOURCE_DIR}/less.cpp)
add_executable(test-self-is ${SELF_SOURCE_DIR}/is.cpp)
add_executable(test-self-in ${SELF_SOURCE_DIR}/in.cpp)

add_executable(test-run-all ${RUN_SOURCE_DIR}/all.cpp)

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

target_link_libraries(test-case-name unittest)
target_link_libraries(test-case-run unittest)

target_link_libraries(test-util-any-of unittest)
target_link_libraries(test-util-all-of unittest)
target_link_libraries(test-util-repr unittest)

target_link_libraries(test-self-greater-equal unittest)
target_link_libraries(test-self-almost-equal unittest)
target_link_libraries(test-self-is-not-null unittest)
target_link_libraries(test-self-less-equal unittest)
target_link_libraries(test-self-not-equal unittest)
target_link_libraries(test-self-greater unittest)
target_link_libraries(test-self-is-null unittest)
target_link_libraries(test-self-is-not unittest)
target_link_libraries(test-self-throws unittest)
target_link_libraries(test-self-equal unittest)
target_link_libraries(test-self-false unittest)
target_link_libraries(test-self-true unittest)
target_link_libraries(test-self-fail unittest)
target_link_libraries(test-self-less unittest)
target_link_libraries(test-self-is unittest)
target_link_libraries(test-self-in unittest)

target_link_libraries(test-run-all unittest)

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

add_test(test-name test-case-name)
add_test(test-run test-case-run)

add_test(util-any-of test-util-any-of)
add_test(util-all-of test-util-all-of)
add_test(util-repr test-util-repr)

add_test(self-greater-equal test-self-greater-equal)
add_test(self-almost-equal test-self-almost-equal)
add_test(self-is-not-null test-self-is-not-null)
add_test(self-less-equal test-self-less-equal)
add_test(self-not-equal test-self-not-equal)
add_test(self-greater test-self-greater)
add_test(self-is-null test-self-is-null)
add_test(self-is-not test-self-is-not)
add_test(self-throws test-self-throws)
add_test(self-equal test-self-equal)
add_test(self-false test-self-false)
add_test(self-true test-self-true)
add_test(self-fail test-self-fail)
add_test(self-less test-self-less)
add_test(self-is test-self-is)
add_test(self-in test-self-in)

add_test(run-all test-run-all)
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

add_dependencies(check test-case-name)
add_dependencies(check test-case-run)

add_dependencies(check test-util-any-of)
add_dependencies(check test-util-all-of)
add_dependencies(check test-util-repr)

add_dependencies(check test-self-greater-equal)
add_dependencies(check test-self-almost-equal)
add_dependencies(check test-self-is-not-null)
add_dependencies(check test-self-less-equal)
add_dependencies(check test-self-not-equal)
add_dependencies(check test-self-greater)
add_dependencies(check test-self-is-null)
add_dependencies(check test-self-is-not)
add_dependencies(check test-self-throws)
add_dependencies(check test-self-equal)
add_dependencies(check test-self-false)
add_dependencies(check test-self-true)
add_dependencies(check test-self-fail)
add_dependencies(check test-self-less)
add_dependencies(check test-self-is)
add_dependencies(check test-self-in)

add_dependencies(check test-run-all)
