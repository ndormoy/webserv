#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Request
{
	public:
		typedef std::map<std::string, std::string> param_type;

	private:
		param_type&	_params;
		int	_method;
		std::string _path;
		std::string _version;
		bool		_chunked;
		int			_error_value;
		string_vector& _lexer;

	public:
		std::string	get_path() { return _path; }
		std::string get_version() { return _version; }
		int			get_error_value() { return _error_value; }
		std::string	get_content_type() { return _params.at("Content-Type"); }
		std::string	get_content_length() { return _params.at("Content-Length"); }
	public:
		Request (void) :
			_method(0),
			_path(""),
			_version(""),
			_chunked(false),
			_error_value(0),
			_params(*new param_type()),
			_lexer(*new string_vector())
		{
			FOREACH_HEADER {
				_params[*it] = "";
			}
			_params["Accept-Language"] = "en";
			_params["Content-Disposition"] = "attachment";
			_params["Connection"] = "keep-alive";
		}

		virtual ~Request (void) {
			_params.clear();
			_lexer.clear();
			delete &_params;
			delete &_lexer;
		}

		Request (const Request & ref) :
			_params(ref._params),
			_method(ref._method),
			_path(ref._path),
			_version(ref._version),
			_chunked(ref._chunked),
			_error_value(ref._error_value),
			_lexer(ref._lexer)
		{ }

		Request (const std::string str) :
			Request()
		{
			_lexer = vector_spliter(str, " ", "\r\n\0", false);
			_chunked = (str.find("\r\n\r\n") == std::string::npos);
			request_parser();
			DEBUG_5(CNOUT(*this));
		}


	public:

		void	request_parser (void);

	public:
		Request & operator= (const Request & ref) {
			if (this == &ref) {return (*this);}

			_method = ref._method;
			_path = ref._path;
			_version = ref._version;
			_chunked = ref._chunked;
			_params = ref._params;
			_error_value = ref._error_value;
			_lexer = ref._lexer;
			return *this;
		}

		friend std::ostream & operator<< (std::ostream & o, const Request & ref) {
			o << "Method: " << ref._method << std::endl;
			o << "Path: " << ref._path << std::endl;
			o << "Version: " << ref._version << std::endl;
			o << "Chunked: " << ref._chunked << std::endl;
			o << "Params: " << std::endl;
			for (std::map<std::string, std::string>::const_iterator it = ref._params.begin(); it != ref._params.end(); ++it) {
				o << "  " << it->first << ": " << it->second << std::endl;
			}
			o << "Lexer: " << std::endl;
			for (string_vector::const_iterator it = ref._lexer.begin(); it != ref._lexer.end(); ++it) {
				o << "  [" << *it << "]";
			}
			return o;
		}

	public:

	
};

_END_NAMESPACE_WEBSERV

#endif
