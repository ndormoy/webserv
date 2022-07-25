#include "../incs/webserv.hpp"
#include <iostream>
#include <fstream>

void	Cgi::find_status_code(void)
{
	_file_size = calculate_size_file((char *)_request.get_path().c_str());
	if (_file_size == -1)
		_status_code = "404 Not Found";
	else
		_status_code = "200 OK";

}