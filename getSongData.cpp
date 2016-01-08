/* 
*	This program receives a single parameter of a song name from the front-end. It then fetches song data from the database and converts it to JSON. This JSON data is then sent back
*	to the client, which processes it and displays the information to the user.
*/

/* Standard Library Headers */
#include <iostream> // cout

/* cgicc headers */
#include <cgicc/Cgicc.h> // Main Cgicc class
#include <cgicc/HTTPHTMLHeader.h> // Class which generates HTTP headers

int main(int argc, char* argv[])
{
	try
	{
		cgicc::Cgicc cgi; // Cgicc object used for processing CGI stuff
	{

	catch (exception& e)
	{
	  cout << cgicc::HTTPHTMLHeader() << endl;
	}
}
