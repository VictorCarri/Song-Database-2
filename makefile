gsd: getSongData.cpp /usr/local/lib/json.cpp # The gsd executable depends on the CGI executable's C++ file and the JSON C++ file
	g++ -lcgicc -lmysqlcppconn -o gsd getSongData.cpp /usr/local/lib/json.cpp 2>&1 # Compile the program using the CgiCC, MySQL, and JSONcpp libs
	mv gsd ../.. # Move the executable to the cgi-bin directory
