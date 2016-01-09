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
#include <cppconn/driver.h> // MySQL driver class
#include <cppconn/exception.h> // MySQL exceptions
#include <cppconn/resultset.h> // MySQL result set class
#include <cppconn/prepared_statement.h> // MySQL PreparedStatement class

/* JSON headers */
#include <json/json.h> // JSONCPP header

/* C Headers */
#include <cstdlib> // exit, EXIT_FAILURE, EXIT_SUCCESS

/**
 * Main function of the program.
 */
int main(int argc, char* argv[])
{
	try
	{
	  /** Variables **/
	  
	  /* CGI vars */
	  cgicc::Cgicc cgi; // Cgicc object used for processing CGI stuff
	  cgicc::CgiEnvironment env = cgi.getEnvironment(); // The environment of the HTTP request
	  
	  /* MySQL vars */
	  sql::Driver *pdriver; // Pointer to MySQL driver object
	  sql::Connection *pconn; // Pointer to MySQL connection object
	  sql::PreparedStatement *ppstmt; // Pointer to MySQL statement object;
	  sql::ResultSet *pres; // Pointer to MySQL resultset object
	  std::stringstream datprep; // The stringstream used to build the LIKE q's datauery
	  std::stringstream resPrep; // The stringstream used to build a JSON result object
	  
	  /* POST request vars */
	  std::string songContentType = env.getContentType(); // Get the content type of the data in the POST request
	  std::string songName = cgi("sname"); // Get the value of the song name parameter
	  
	  /** Query the database with the song name to get information about the song **/
	  
	  /* Create a connection */
	  pdriver = get_driver_instance(); // Get an instance of a driver
	  pconn = pdriver->connect("tcp://127.0.0.1:3306", "root", "1124mania"); // Connect to MySQL
	  pconn->setSchema("personal"); // Select the personal database
	  
	  /* Create and execute the statement */
	  ppstmt = pconn->prepareStatement("SELECT * FROM songs WHERE `Title` LIKE ?"); // Prepare the SELECT statement for SQL
	  datprep << "%" << songName << "%"; // Set the string in datprep to the user's parameter enclosed by percent signs (global match with LIKE)
	  ppstmt->setString(1, datprep.str()); // Add the user's input to the query
	  pres = ppstmt->executeQuery(); // Execute the query and store a pointer to the results
	  
	  std::cout << "Content-Type: application/json\r\n\r\n"; // HTTP header, letting browser know that what follows is JSON
	  
	  while (pres->next()) // Loop through all of the results in the result set
	  {
	    std::cout << pres->getInt(1) << std::endl; // DEBUGGING: Print ID
	  }
	  
	  /* Cleanup resources */
	  delete pres; // Delete the result set
	  delete ppstmt; // Delete the prepared statement
	  delete pconn; // Free the connection
	  
	  return EXIT_SUCCESS; // Indicate successful completion
	}
	
	catch (sql::SQLException& sqlError) // Catch any exceptions thrown by MySQL
	{
	  std::stringstream exss;
	  
	  /* Generate the error message */
	  exss << "# ERR: SQLException in " << __FILE__;
	  exss << "(" << __FUNCTION__ << ") on line »" 
	   << __LINE__ << std::endl;
	  exss << "# ERR: " << sqlError.what();
	  exss << " (MySQL error code: " << sqlError.getErrorCode();
	  exss << ", SQLState: " << sqlError.getSQLState() << " )" << std::endl;
	  
	  /* Send the HTTP headers and the error message */
	  std::cout << cgicc::HTTPHTMLHeader() << exss.str(); // Send the error message
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
