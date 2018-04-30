add_library(rvk SHARED rvk_stub.cpp)
generate_export_header(rvk)
set_property(TARGET rvk PROPERTY CXX_STANDARD_REQUIRED 11)

target_link_libraries(rvk PUBLIC TurboJpeg Snappy::snappy glm Threads::Threads)
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

