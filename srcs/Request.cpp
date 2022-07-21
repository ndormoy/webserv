#include "webserv.hpp"

Request::Request(void)
{
	_params = {
		{"Accept-Charset", ""},
		{"Accept-Encoding", ""},
		{"Accept-Language", "en"},
		{"Accept",""},
		{"Auth-Scheme",""},
		{"Autorization",""},
		{"Content-Type", ""},
		{"Content-Length", ""},
		{"Content-Location", ""},
		{"Content-Type", ""},
		{"Connection", "keep-alive"},
		{"Cookie",""},
		{"Host",""},
		{"Date", ""},
		{"Last-Modified", ""},
		{"Location", ""},
		{"Retry-After", ""},
		{"Transfer-encoding", ""},
		{"Set-Cookie", ""},
		{"Origin",""},
		{"Referer",""},
		{"From", ""}
		};
	_method = 0;
	_path = "";
}