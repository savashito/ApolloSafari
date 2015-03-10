
cmake_minimum_required(VERSION 2.8)
project( simplar )
FIND_LIBRARY(ZMQ_LIB libzmq)
find_package( OpenCV REQUIRED )
add_executable( app simplar.cpp )
target_link_libraries( app ${OpenCV_LIBS}  )
target_link_libraries( app "-lzmq" ) 
