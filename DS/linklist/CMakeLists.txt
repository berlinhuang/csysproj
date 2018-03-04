set(intv_SRCS
        linklist.c
        )
add_library(intv ${intv_SRCS})


add_executable(atoi atoi.c)
target_link_libraries(atoi intv)