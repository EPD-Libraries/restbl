add_executable(restbl_test
    ./src/include/utils/file_util.h
    ./src/main.cpp
)

target_include_directories(restbl_test PRIVATE ./src/include)
target_link_libraries(restbl_test PUBLIC restbl)
