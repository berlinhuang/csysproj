set(intv_SRCS
        INTV.c
        )
add_library(intv ${intv_SRCS})


add_executable(linklist linklist.c)
target_link_libraries(linklist intv)



add_executable(atoi atoi.c)
target_link_libraries(atoi intv)