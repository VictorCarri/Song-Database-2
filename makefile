gsd: getSongData.cpp # The gsd executable depends on the C++ file
	g++ -lcgicc -lmysqlcppconn -Ljson -o gsd getSongData.cpp 2>&1 # Compile the program using the CgiCC, MySQL, and JSONcpp libs
	mv gsd ../.. # Move the executable to the cgi-bin directory
