set(sort_SRCS
        sort.c
        ../tree/BinTree.h)
add_library(sort ${sort_SRCS})


add_executable(sort_quick quicksort.c)
target_link_libraries(sort_quick sort)

add_executable(sort_insert insertsort.c)
target_link_libraries(sort_insert sort)

add_executable(sort_bininsert bininsesort.c)
target_link_libraries(sort_bininsert sort)

add_executable(sort_bubble bubblesort.c)
target_link_libraries(sort_bubble sort)

add_executable(sort_select selectsort.c)
target_link_libraries(sort_select sort)

add_executable(sort_shell shellsort.c)
target_link_libraries(sort_shell sort)

add_executable(sort_heap heapsort.c)
target_link_libraries(sort_heap sort)

add_executable(sort_merge mergesort.c)
target_link_libraries(sort_merge sort)