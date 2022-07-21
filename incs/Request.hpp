#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "webserv.hpp"

class Request
{
	public:
		Request(void)
		{
			_params["Accept-Charset"] = "";
			_params["Accept-Encoding"] = "";
			_params["Accept-Language"] = "en";
			_params["Accept"] ="";
			_params["Auth-Scheme"] ="";
			_params["Autorization"] ="";
			_params["Content-Type"] = "";
			_params["Content-Length"] = "";
			_params["Content-Location"] = "";
			_params["Content-Type"] = "";
			_params["Content-Disposition"] = "attachment";
			_params["Connection"] = "keep-alive";
			_params["Cookie"] ="";
			_params["Host"] ="";
			_params["Date"] = "";
			_params["Last-Modified"] = "";
			_params["Location"] = "";
			_params["Retry-After"] = "";
			_params["Transfer-encoding"] = "";
			_params["Set-Cookie"] = "";
			_params["Origin"] = "";
			_params["Referer"] ="";
			_params["From"] = "";
			_method = 0;
			_path = "";
		}

		~Request();

		void	parse_request(void);
	private:
		std::map<std::string, std::string>	_params;
		int	_method;
		std::string _path;
};

#endif