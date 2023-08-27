# get google test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
  # URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ac_test
    ac_int_test.cpp       
    ac_fixed_test.cpp       
)

target_link_libraries(
  ac_test
  ac_types
  # GTest::gtest_main
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(ac_test)