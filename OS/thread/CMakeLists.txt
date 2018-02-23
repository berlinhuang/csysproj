add_executable(compete compete.c)
target_link_libraries(compete pthread)

add_executable(mutex mutex.c)
target_link_libraries(mutex pthread)

add_executable(condition condition.c)
target_link_libraries(condition pthread)

add_executable(rwlock rwlock.c)
target_link_libraries(rwlock pthread)

add_executable(semaphore semaphore.c)
target_link_libraries(semaphore pthread)