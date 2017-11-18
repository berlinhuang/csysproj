set(sort_SRCS
        sort.c
        )
add_library(sort ${sort_SRCS})


add_executable(quicksort quicksort.c)
target_link_libraries(quicksort sort)

add_executable(insertsort insertsort.c)
target_link_libraries(insertsort sort)

add_executable(bininsesort bininsesort.c)
target_link_libraries(bininsesort sort)

add_executable(bubblesort bubblesort.c)
target_link_libraries(bubblesort sort)

add_executable(selectsort selectsort.c)
target_link_libraries(selectsort sort)

add_executable(shellsort shellsort.c)
target_link_libraries(shellsort sort)

add_executable(heapsort heapsort.c)
target_link_libraries(heapsort sort)

add_executable(mergesort mergesort.c)
target_link_libraries(mergesort sort)