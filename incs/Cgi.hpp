#ifndef CGI_HPP
# define CGI_HPP

# include "webserv.hpp"

class Cgi
{
	public:
		Cgi();
		Cgi(Request const & request) : _request(request), _file_size(0) {};
		Cgi(const Cgi & copy);

		~Cgi();

		Cgi & operator=(const Cgi & copy);

		int calculate_size_file(char *filename);
		void	find_status_code(void);
	private:

		int			_file_size;
		std::string	_status_code;
		Request		_request;
};

#endif
