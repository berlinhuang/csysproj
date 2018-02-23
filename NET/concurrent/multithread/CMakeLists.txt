
add_executable(thread_client thread_client.c)
target_link_libraries(thread_client wrap)


add_executable(thread_server thread_server.c)
target_link_libraries(thread_server wrap)