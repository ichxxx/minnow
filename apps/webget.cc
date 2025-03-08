#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

const static std::string METHOD_GET        = "GET";
const static std::string HTTP_1_1          = "HTTP/1.1";
const static std::string HEADER_HOST       = "Host";
const static std::string HEADER_CONNECTION = "Connection";
const static std::string CRLF = "\r\n";

void get_URL( const string& host, const string& path )
{
  TCPSocket socket;
  socket.connect( Address( host, "http" ) );

  socket.write( { 
    METHOD_GET, " ", path, " ", HTTP_1_1, CRLF,
    HEADER_HOST, ": ", host, CRLF,
    HEADER_CONNECTION, ": ", "close", CRLF,
    CRLF
  } );

  std::string resp_buffer;
  while ( !socket.eof() && !socket.closed() ) {
    socket.read( resp_buffer );
    cout << resp_buffer;
  }
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
