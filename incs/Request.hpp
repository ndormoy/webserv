#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "webserv.hpp"

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
		string_vector& _lexer;

	public:
		Request (void) :
			_method(0),
			_path(""),
			_version(""),
			_chunked(false),
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
			_lexer(ref._lexer)
		{
			if (this == &ref) {return (*this);}
		}


	public:

		void	request_parser(void);

	public:
		Request & operator= (const Request & ref) {
			if (this == &ref) {return (*this);}

			_method = ref._method;
			_path = ref._path;
			_version = ref._version;
			_chunked = ref._chunked;
			_params = ref._params;
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
			return o;
		}

	public:

	
};

#endif
