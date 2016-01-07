/* 
*	This program receives a single parameter of a song name from the front-end. It then fetches song data from the database and converts it to JSON. This JSON data is then sent back
*	to the client, which processes it and displays the information to the user.
*/

/* Headers */
#include <iostream> // cout

using namespace std;

/*
* Separates sections of an HTTP request
*/
void sepSecs()
{
	cout << "\r\n\r\n";
}

/*
*	Sends the HTTP headers
*/
void sendHeaders()
{
	cout << "Content-Type: text/html";	// Content-Type header
	sepSecs();	// End the header section
}

/*
*	Generates a test page, to see if the program is working
*/
void testPage()
{
	cout << "<html><head><title>Test page</title></head><body>Can you see me?</body></html>"; // Send the test page data
	sepSecs();	// End the content section
}

int main()
{
	sendHeaders();	// Send the HTTP headers
	testPage();	// Generate a test page
}
