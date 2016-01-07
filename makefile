gsd: getSongData.cpp # The gsd executable depends on the C++ file
	g++ -o gsd getSongData.cpp # Compile the file
	mv gsd ../.. # Move the executable to the cgi-bin directory
