add_library(rvk SHARED
	reader_writer.cpp write_buffer.cpp read_buffer.cpp
	tcp.cpp)
generate_export_header(rvk)
set_property(TARGET rvk PROPERTY CXX_STANDARD 14)
set_property(TARGET rvk PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(rvk PUBLIC TurboJpeg Snappy::snappy glm Threads::Threads)
if (WIN32)
	target_link_libraries(rvk PUBLIC wsock32 ws2_32)
endif()

target_include_directories(rvk PUBLIC
	$<BUILD_INTERFACE:${rvk_BINARY_DIR}>
	$<BUILD_INTERFACE:${rvk_SOURCE_DIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
	$<INSTALL_INTERFACE:include>
)

# TODO Provide an example

install(TARGETS rvk EXPORT rvkConfig
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)
install(FILES rvk.h ${CMAKE_CURRENT_BINARY_DIR}/rvk_export.h
	DESTINATION include/rvk
)
install(EXPORT rvkConfig
	DESTINATION lib/cmake/rvk
)

