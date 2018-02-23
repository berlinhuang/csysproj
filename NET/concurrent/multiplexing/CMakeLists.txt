
add_executable(select_client select_client.c)
target_link_libraries(select_client wrap)

add_executable(select_server select_server.c)
target_link_libraries(select_server wrap)


add_executable(poll_client poll_client.c)
target_link_libraries(poll_client wrap)

add_executable(poll_server poll_server.c)
target_link_libraries(poll_server wrap)



add_executable(epoll_client epoll_client.c)
target_link_libraries(epoll_client wrap)

add_executable(epoll_server epoll_server.c)
target_link_libraries(epoll_server wrap)

add_executable(epoll epoll.cpp)