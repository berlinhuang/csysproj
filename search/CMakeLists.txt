set(search_SRCS
        search.c
        )
add_library(search ${search_SRCS})


add_executable(seqsearch seqsearch.c)
target_link_libraries(seqsearch search)


add_executable(binsearch binsearch.c)
target_link_libraries(binsearch search)
