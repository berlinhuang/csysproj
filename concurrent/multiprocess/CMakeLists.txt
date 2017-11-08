
add_executable(process_client process_client.c)
target_link_libraries(process_client wrap)


add_executable(process_server process_server.c)
target_link_libraries(process_server wrap)