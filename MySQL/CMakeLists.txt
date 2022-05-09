include_directories(/usr/include/mysql)
link_directories(/usr/lib/x86_64-linux-gnu)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_library(mymysql mysql_conn.cpp Singleton.cpp)
target_link_libraries(mymysql -lmysqlclient)


add_executable(testmysql test_mysql.cpp)
target_link_libraries(testmysql mymysql)


set(EXECUTABLE_OUTPUT_PATH   ${PROJECT_SOURCE_DIR}/MySQL)
#message(${PROJECT_SOURCE_DIR})
add_executable(testmysqlconnpool  Singleton.cpp MySQLConn.cpp MySQLConnPool.cpp test_mysql_connpool.cpp)
target_link_libraries(testmysqlconnpool -lmysqlclient -lpthread)