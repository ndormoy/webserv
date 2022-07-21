#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "webserv.hpp"

class Request
{
	public:
		Request(void);

		~Request();
	private:
		std::map<std::string, std::string>	_params;
		int	_method;
		std::string _path;
};

#endif