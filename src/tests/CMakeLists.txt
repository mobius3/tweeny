cmake_minimum_required(VERSION 3.15)
find_package(Catch2 3 REQUIRED CONFIG)

add_executable(tweeny_tests
    sanity.cpp
    tween/peek.cpp
    tween/progress.cpp
    tween/step.cpp
    tween/seek.cpp
    tween/jump.cpp
    events/step.cpp
    events/seek.cpp
    events/jump.cpp
    events/complete.cpp
    events/keyframe_enter.cpp
    events/keyframe_leave.cpp
    events/update.cpp
)

target_compile_features(tweeny_tests PRIVATE cxx_std_17)
target_link_libraries(tweeny_tests PRIVATE Catch2::Catch2WithMain tweeny::tweeny)

include(Catch)
catch_discover_tests(tweeny_tests)
