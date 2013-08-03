add_custom_target(check COMMAND ${CMAKE_TEST_COMMAND})

# TODO: Do a check if RTTI is disabled and remove the equivalent tests (type)
#       if it is.

#------------------------------------------------------------------------------
# Set Variables
#------------------------------------------------------------------------------
set(TASK_SOURCE_DIR "${TEST_SOURCE_DIR}/task")
set(SKIP_SOURCE_DIR "${TEST_SOURCE_DIR}/skip")
set(UTIL_SOURCE_DIR "${TEST_SOURCE_DIR}/util")
set(SELF_SOURCE_DIR "${TEST_SOURCE_DIR}/assert")
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

add_executable(test-util-any-of ${UTIL_SOURCE_DIR}/any-of.cpp)
add_executable(test-util-all-of ${UTIL_SOURCE_DIR}/all-of.cpp)
add_executable(test-util-repr ${UTIL_SOURCE_DIR}/repr.cpp)

add_executable(test-assert-not-almost-equal ${SELF_SOURCE_DIR}/not-almost.cpp)
add_executable(test-assert-greater-equal ${SELF_SOURCE_DIR}/greater-equal.cpp)
add_executable(test-assert-almost-equal ${SELF_SOURCE_DIR}/almost-equal.cpp)
add_executable(test-assert-is-not-null ${SELF_SOURCE_DIR}/is-not-null.cpp)
add_executable(test-assert-less-equal ${SELF_SOURCE_DIR}/less-equal.cpp)
add_executable(test-assert-not-equal ${SELF_SOURCE_DIR}/not-equal.cpp)
add_executable(test-assert-greater ${SELF_SOURCE_DIR}/greater.cpp)
add_executable(test-assert-is-null ${SELF_SOURCE_DIR}/is-null.cpp)
add_executable(test-assert-is-not ${SELF_SOURCE_DIR}/is-not.cpp)
add_executable(test-assert-throws ${SELF_SOURCE_DIR}/throws.cpp)
add_executable(test-assert-equal ${SELF_SOURCE_DIR}/equal.cpp)
add_executable(test-assert-fail ${SELF_SOURCE_DIR}/fail.cpp)
add_executable(test-assert-less ${SELF_SOURCE_DIR}/less.cpp)
add_executable(test-assert-is ${SELF_SOURCE_DIR}/is.cpp)
add_executable(test-assert-in ${SELF_SOURCE_DIR}/in.cpp)

add_executable(test-run-all ${RUN_SOURCE_DIR}/all.cpp)

#------------------------------------------------------------------------------
# Test Section
#------------------------------------------------------------------------------
add_test(task-name test-task-name)
add_test(task-call test-task-call)
add_test(task-type test-task-type)

add_test(skip-default test-skip-default)
add_test(skip-unless test-skip-unless)
add_test(skip-if test-skip-if)

add_test(util-any-of test-util-any-of)
add_test(util-all-of test-util-all-of)
add_test(util-repr test-util-repr)

add_test(assert-not-almost-equal test-assert-not-almost-equal)
add_test(assert-greater-equal test-assert-greater-equal)
add_test(assert-almost-equal test-assert-almost-equal)
add_test(assert-is-not-null test-assert-is-not-null)
add_test(assert-less-equal test-assert-less-equal)
add_test(assert-not-equal test-assert-not-equal)
add_test(assert-greater test-assert-greater)
add_test(assert-is-null test-assert-is-null)
add_test(assert-is-not test-assert-is-not)
add_test(assert-throws test-assert-throws)
add_test(assert-equal test-assert-equal)
add_test(assert-fail test-assert-fail)
add_test(assert-less test-assert-less)
add_test(assert-is test-assert-is)
add_test(assert-in test-assert-in)

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

add_dependencies(check test-util-any-of)
add_dependencies(check test-util-all-of)
add_dependencies(check test-util-repr)

add_dependencies(check test-assert-not-almost-equal)
add_dependencies(check test-assert-greater-equal)
add_dependencies(check test-assert-almost-equal)
add_dependencies(check test-assert-is-not-null)
add_dependencies(check test-assert-less-equal)
add_dependencies(check test-assert-not-equal)
add_dependencies(check test-assert-greater)
add_dependencies(check test-assert-is-null)
add_dependencies(check test-assert-is-not)
add_dependencies(check test-assert-throws)
add_dependencies(check test-assert-equal)
add_dependencies(check test-assert-fail)
add_dependencies(check test-assert-less)
add_dependencies(check test-assert-is)
add_dependencies(check test-assert-in)

add_dependencies(check test-run-all)
