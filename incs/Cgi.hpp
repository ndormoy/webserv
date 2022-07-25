#ifndef CGI_HPP
# define CGI_HPP

# include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Cgi
{
	public:
		Cgi();
		Cgi(Request const & request) :
			_request(request),
			_file_size(0),
			_header("HTTP/1.1 ")
			{};
		Cgi(const Cgi & copy);

		~Cgi();

		Cgi & operator=(const Cgi & copy);

		void	fill_status_code(void);
		void 	fill_header(void);
		void	fill_body(void);
		void	manage_response(void);
		std::string auto_index(void);
		void	create_index(void);
	
	private:

		int			_file_size;
		std::string	_header;
		Request		_request;
		string_vector	_files;
};

_END_NAMESPACE_WEBSERV

#endif
