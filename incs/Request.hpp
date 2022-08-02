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
		int			_method;
		std::string _path;
		std::string _construct_path;
		std::string _version;
		bool		_chunked;
		int			_error_value;
		std::string _query_string;
		Server *	_server;
		Location *  _location;
		std::string _body;


	public:
		Request (void) :
			_params(*new param_type()),
			_method(0),
			_path(""),
			_construct_path(""),
			_version(""),
			_chunked(false),
			_error_value(0),
			_query_string(""),
			_server(NULL),
			_location(NULL),
			_body("")
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
			delete &_params;
		}

		Request (const Request & ref) :
			_params(ref._params),
			_method(ref._method),
			_path(ref._path),
			_construct_path(ref._construct_path),
			_version(ref._version),
			_chunked(ref._chunked),
			_error_value(ref._error_value),
			_query_string(ref._query_string),
			_server(ref._server),
			_location(ref._location),
			_body(ref._body)
		{ }

		Request (const std::string str) :
			_params(*new param_type()),
			_method(0),
			_path(""),
			_construct_path(""),
			_version(""),
			_chunked(false),
			_error_value(0),
			_query_string(""),
			_server(NULL),
			_location(NULL),
			_body("")
		{
			_body = str;
			//CNOUT(BYEL << _body << CRESET)
			_chunked = (str.find("\r\n\r\n") == std::string::npos);
			_error_value = request_parser();
			DEBUG_5(CNOUT(*this));
		}

	public:

		param_type & 			get_params (void) const 		{ return (_params); }
		int						get_method (void) const				{ return (_method); }
		std::string				get_path (void) const				{ return (_path); }
		std::string				get_construct_path (void) const 	{ return (_construct_path); }
		std::string				get_version (void) const				{ return (_version); }
		bool					get_chunked (void) const				{ return (_chunked); }
		std::string 			get_body (void)const 				{ return (_body); }
		int						get_error_value (void)const			{ return (_error_value); }
		std::string 			get_query_string (void) const		{ return (_query_string); }
		Server *				get_server (void) const				{ return (_server); }
		Location *				get_location (void) const			{ return (_location); }
		std::string				get_params (std::string str) const	{ return (_params.at(str)); }

		void					set_chunked (bool b) 			{ _chunked = b; }
		void					set_error_value (int i)			{ _error_value = i; }

		void					clear (void) {
			_params.clear();
			_method = 0;
			_path = "";
			_construct_path = "";
			_version = "";
			_chunked = false;
			_error_value = 0;
			_body = "";
			_query_string = "";
			_server = NULL;
			_location = NULL;
		}

	public:

		int		request_parser (void);
		int		check_first_line (void);
		bool	parse_first_line (std::string);
		void	request_line_parser (std::string);
		void	set_final_path (void);
		bool	is_upload_case(void);
	public:
	
		Request & operator= (const Request & ref) {
			if (this == &ref) {return (*this);}

			_method = ref._method;
			_path = ref._path;
			_construct_path = ref._construct_path;
			_version = ref._version;
			_chunked = ref._chunked;
			_params = ref._params;
			_body = ref._body;
			_error_value = ref._error_value;
			_query_string = ref._query_string;
			_server = ref._server;
			_location = ref._location;
			return *this;
		}

		friend std::ostream & operator<< (std::ostream & o, const Request & ref) {
			o << "Method: " << ref._method << std::endl;
			o << "Path: " << ref._path << std::endl;
			o << "Construct path: " << ref._construct_path << std::endl;
			o << "Version: " << ref._version << std::endl;
			o << "Chunked: " << ref._chunked << std::endl;
			o << "Body: " << ref._body << std::endl;
			o << "Error value: " << ref._error_value << std::endl;
			o << "Query string: " << ref._query_string << std::endl;
			o << "Server: " << ref._server << std::endl;
			o << "Location: " << ref._location << std::endl;
			o << "Params: " << std::endl;
			for (std::map<std::string, std::string>::const_iterator it = ref._params.begin(); it != ref._params.end(); ++it) {
				o << " -> " << it->first << ": " << it->second << std::endl;
			}

			return o;
		}
	
};

_END_NAMESPACE_WEBSERV

#endif
