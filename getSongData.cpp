/* 
*	This program receives a single parameter of a song name from the front-end. It then fetches song data from the database and converts it to JSON. This JSON data is then sent back
*	to the client, which processes it and displays the information to the user.
*/

/** C++ Headers **/

/* C++ STL Headers */
#include <iostream> // cout
#include <sstream> // stringstream
#include <string> // string

/* cgicc headers */
#include <cgicc/CgiDefs.h> // Platform-and-system-specific def'ns
#include <cgicc/Cgicc.h> // Main Cgicc class
#include <cgicc/HTTPHTMLHeader.h> // Class which generates HTTP headers
#include <cgicc/HTMLClasses.h> // Defines the HTML classes

/* MySQL */
#include "mysql_connection.h" // MySQL connection header

/*/ MySQL C++ connector headers */
#include <cppconn/driver.h> // MySQL driver
#include <cppconn/exception.h> // MySQL exceptions
#include <cppconn/resultset.h> // MySQL result set classes
#include <cppconn/statement.h> // MySQL statement object

/* C Headers */
#include <cstdlib> // exit, EXIT_FAILURE, EXIT_SUCCESS

int main(int argc, char* argv[])
{
	try
	{
	  /** Variables **/
	  
	  /* CGI vars */
	  cgicc::Cgicc cgi; // Cgicc object used for processing CGI stuff
	  
	  /* MySQL vars */
	  sql::Driver *driver; // MySQL driver object
	  sql::Connection *conn; // MySQL connection object
	  sql::Statement *stmt; // MySQL statement object;
	  sql::ResultSet *res; // MySQL resultset object
	  
	  /* Program vars*/
	  std::stringstream ss; // Stringstream used to build div text
	  
	  ss << "Hi, I'm " << __FILE__ << ", and I'm executing my " << __FUNCTION__ << " function now.";
	  
	  /* Print headers and doctype */
	  std::cout << cgicc::HTTPHTMLHeader() << "<!DOCTYPE html>" << std::endl; // Print the Content-Type header, but use an HTML5 doctype, not an HTML4 one
	  
	  /* Start HTML */
	  std::cout << cgicc::html().set("lang", "en") << cgicc::head(cgicc::title("CGI Test"))/* << cgicc::head() */<< cgicc::body(cgicc::div(ss.str()))/* << cgicc::body() */<< cgicc::html() << std::endl; // Prints some test HTML
	  
	  return EXIT_SUCCESS; // Indicate successful completion
	}
	
	catch (sql::SQLException& sqlError) // Catch any exceptions thrown by MySQL
	{
	  std::cout << "# ERR: SQLException in " << __FILE__;
	  std::cout << "(" << __FUNCTION__ << ") on line »" 
	   << __LINE__ << std::endl;
	  std::cout << "# ERR: " << sqlError.what();
	  std::cout << " (MySQL error code: " << sqlError.getErrorCode();
	  std::cout << ", SQLState: " << sqlError.getSQLState() << " )" << std::endl;
	}

	catch (const std::exception& otherError) // Catch any exceptions thrown while processing the request
	{
	  // This is a dummy exception handler, as it doesn't really do
	     // anything except print out information.
	 
	     // Reset all the HTML elements that might have been used to 
	     // their initial state so we get valid output
	     cgicc::html::reset();      cgicc::head::reset();          cgicc::body::reset();
	     cgicc::title::reset();     cgicc::h1::reset();            cgicc::h4::reset();
	     cgicc::comment::reset();   cgicc::td::reset();            cgicc::tr::reset(); 
	     cgicc::table::reset();     cgicc::div::reset();    cgicc::p::reset(); 
	     cgicc::a::reset();         cgicc::h2::reset();            cgicc::colgroup::reset();
	 
	     // Output the HTTP headers for an HTML document, and the HTML 4.0 DTD info
	     std::cout << cgicc::HTTPHTMLHeader() << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
	     std::cout << cgicc::html().set("lang","en").set("dir","ltr") << std::endl;
	 
	     // Set up the page's header and title.
	     // I will put in lfs to ease reading of the produced HTML. 
	     std::cout << cgicc::head() << std::endl;
	 
	     // Output the style sheet portion of the header
	     std::cout << cgicc::style() << cgicc::comment() << std::endl;
	     std::cout << "body { color: black; background-color: white; }" << std::endl;
	     std::cout << "hr.half { width: 60%; align: center; }" << std::endl;
	     std::cout << "span.red, STRONG.red { color: red; }" << std::endl;
	     std::cout << "div.notice { border: solid thin; padding: 1em; margin: 1em 0; "
	          << "background: #ddd; }" << std::endl;
	 
	     std::cout << cgicc::comment() << cgicc::style() << std::endl;
	 
	     std::cout << cgicc::title("GNU cgicc exception") << std::endl;
	     std::cout << cgicc::head() << std::endl;
	     
	     std::cout << cgicc::body() << std::endl;
	     
	     std::cout << cgicc::h1() << "GNU cgi" << cgicc::span("cc", cgicc::set("class","red"))
	          << " caught an exception" << cgicc::h1() << std::endl; 
	   
	     std::cout << cgicc::div().set("align","center").set("class","notice") << std::endl;
	 
	     std::cout << cgicc::h2(otherError.what()) << std::endl;
	 
	     // End of document
	     std::cout << cgicc::div() << std::endl;
	     std::cout << cgicc::hr().set("class","half") << std::endl;
	     std::cout << cgicc::body() << cgicc::html() << std::endl;
	     
	     return EXIT_FAILURE;
	}
}
