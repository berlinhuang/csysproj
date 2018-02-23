add_library(bintree BinTree.c)


add_executable(bintree_test bintree_test.c)
target_link_libraries(bintree_test bintree)