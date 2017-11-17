set(sort_SRCS
        sort.c
        )
add_library(sort ${sort_SRCS})


add_executable(quicksort quicksort.c)
target_link_libraries(quicksort sort)


add_executable(insertsort insertsort.c)
target_link_libraries(insertsort sort)