include_directories(/usr/include/mysql)
link_directories(/usr/lib/x86_64-linux-gnu)
set(CMAKE_VERBOSE_MAKEFILE ON)


set(EXECUTABLE_OUTPUT_PATH   ${PROJECT_SOURCE_DIR}/MySQL)
#message(${PROJECT_SOURCE_DIR})
add_executable(testmysqlconnpool singleton.cpp mysqlconn.cpp mysqlconnpool.cpp test_mysql_connpool.cpp)
target_link_libraries(testmysqlconnpool -lmysqlclient -lpthread)