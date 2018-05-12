add_executable(test_tcp test_tcp.cpp)
set_property(TARGET test_tcp PROPERTY CXX_STANDARD 14)
set_property(TARGET test_tcp PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(test_tcp PUBLIC rvk)

