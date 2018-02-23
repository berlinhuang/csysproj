set(search_SRCS
        search.c
        )
add_library(search ${search_SRCS})


add_executable(search_seq seqsearch.c)
target_link_libraries(search_seq search)


add_executable(search_bin binsearch.c)
target_link_libraries(search_bin search)
