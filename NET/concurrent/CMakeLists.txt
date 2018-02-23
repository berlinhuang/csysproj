set(wrap_SRCS
        wrap.c
        )
add_library(wrap ${wrap_SRCS})
target_link_libraries(wrap pthread)

#set_target_properties(engine PROPERTIES COMPILE_FLAGS "-std=c++0x")



add_subdirectory(multithread)
add_subdirectory(multiprocess)
add_subdirectory(multiplexing)
