#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "webserv.hpp"

class Request
{
	public:
		Request(void);

		~Request();
	private:
		int	_method;
		std::string _path;
		std::string _host;
		std::string _user_agent;
		std::string _referer;
		std::string _accept;
		std::string _accept_language;
		std::string _accept_encoding;
		std::string _accept_charset;
		std::string _connection;
		std::string _cookie;
		std::string _content_type;
		std::string _content_length;
};

#endif