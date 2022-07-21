#include "webserv.hpp"

Request::Request(void)
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