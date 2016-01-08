gsd: getSongData.cpp # The gsd executable depends on the C++ file
	g++ -lcgicc -o gsd getSongData.cpp 2>&1 # Compile the program using the CgiCC libs
	mv gsd ../.. # Move the executable to the cgi-bin directory
