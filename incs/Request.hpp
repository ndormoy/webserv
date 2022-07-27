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
		std::string _body;
		string_vector& _lexer;


	public:
		Request (void) :
			_params(*new param_type()),
			_method(0),
			_path(""),
			_version(""),
			_chunked(false),
			_error_value(0),
			_body(""),
			_lexer(*new string_vector())
		{
			FOREACH_HEADER {
				_params[*it] = " ";
				CNOUT(*it)
			}
			_params["Accept-Language:"] = "en";
			_params["Content-Disposition:"] = "attachment";
			_params["Connection:"] = "keep-alive";
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
			_body(""),
			_lexer(ref._lexer)
		{ }

		Request (const std::string str) :
			_params(*new param_type()),
			_method(0),
			_path(""),
			_version(""),
			_chunked(false),
			_error_value(0),
			_body(""),
			_lexer(*new string_vector())
		{
			_body = str;
			_lexer = vector_spliter(str, " ", "\r\n\0", false);
			_chunked = (str.find("\r\n\r\n") == std::string::npos);
			_error_value = request_parser();
			DEBUG_5(CNOUT(*this));
		}

	public:

		param_type & 			get_params (void) const 				{ return (_params); }
		int						get_method (void) 				{ return (_method); }
		std::string				get_path (void) 				{ return (_path); }
		std::string				get_version (void) 				{ return (_version); }
		bool					get_chunked (void) 				{ return (_chunked); }
		std::string 			get_body (void) 				{ return (_body); }
		int						get_error_value (void) 			{ return (_error_value); }
		string_vector& 			get_lexer (void) 				{ return (_lexer); }
		std::string				get_content_type() { return _params.at("Content-Type:"); }
		std::string				get_content_length() { return _params.at("Content-Length:"); }
		std::string				get_autoindex() { return _params.at("Autoindex:"); }
		void					clear (void) {
			_params.clear();
			_lexer.clear();
			_method = 0;
			_path = "";
			_version = "";
			_chunked = false;
			_error_value = 0;
			_body = "";
		}

	public:

		int	request_parser (void);
		int check_first_line (void);

	public:
		Request & operator= (const Request & ref) {
			if (this == &ref) {return (*this);}

			_method = ref._method;
			_path = ref._path;
			_version = ref._version;
			_chunked = ref._chunked;
			_params = ref._params;
			_body = ref._body;
			_error_value = ref._error_value;
			_lexer = ref._lexer;
			return *this;
		}

		friend std::ostream & operator<< (std::ostream & o, const Request & ref) {
			o << "Method: " << ref._method << std::endl;
			o << "Path: " << ref._path << std::endl;
			o << "Version: " << ref._version << std::endl;
			o << "Chunked: " << ref._chunked << std::endl;
			o << "Body: " << ref._body << std::endl;
			o << "Error value: " << ref._error_value << std::endl;
			o << "Params: " << std::endl;
			for (std::map<std::string, std::string>::const_iterator it = ref._params.begin(); it != ref._params.end(); ++it) {
				o << "  " << it->first << " " << it->second << std::endl;
			}
			o << "Lexer: " << std::endl;
			for (string_vector::const_iterator it = ref._lexer.begin(); it != ref._lexer.end(); ++it) {
				o << "  [" << *it << "]";
			}
			return o;
		}
	
};

_END_NAMESPACE_WEBSERV

#endif
