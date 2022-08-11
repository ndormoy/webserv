#ifndef HEADER_HPP
# define HEADER_HPP

# include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Reponse;

class Header
{
	private:
		/* data */
		std::string	_header;
		std::string	_content_type;
		std::string	_content_length;
		std::string _status;
		// std::string	_content_encoding;
		int			_status_code;

	public: /* Constructors */

		Header (void) 
		{ }

		Header(const Request & request): 
			_header("HTTP/1.1 "),
			_content_type("Content-Type: "),
			_content_length("Content-Length: "),
			// _content_encoding("Content-Encoding: "),
			_status_code(request.get_status_code())
		{ }

		~Header()
		{ }

		Header(const Header & copy) {
			*this = copy;
		}

	public: /* Accessors */
		void		set_header(std::string header) 			{ _header = header; }
		void		set_content_type(std::string type) 		{ _content_type = type; }
		void		set_status(std::string status) 			{ _status = status; }
		void		set_content_length(std::string length)	{ _content_length = length; }
		void		set_status_code(int value) 				{ _status_code = value; }
		std::string	get_header(void) const 					{ return _header; }
		std::string	get_content_type(void) const 			{ return _content_type; }
		std::string get_status(void) const 					{ return _status; }
		std::string	get_content_length(void) const 			{ return _content_length; }
		int			get_status_code(void) const 			{ return _status_code; }
	
	public: /* Methods */
		void	fill(const Response & response);

	public: /* Operators */
		Header & operator=(const Header & copy) {
			_header = copy._header;
			_content_type = copy._content_type;
			_content_length = copy._content_length;
			_status_code = copy._status_code;
			return *this;
		}

		friend std::ostream& operator<< (std::ostream& o, const Header & ref) {
			o << ref._header << std::endl;
			o << ref._content_type << std::endl;
			o << ref._content_length << std::endl;
			o << ref._status_code << std::endl;
			return o;
		}


};




_END_NAMESPACE_WEBSERV

#endif