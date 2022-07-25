#ifndef CGI_HPP
# define CGI_HPP

# include "webserv.hpp"

class Cgi
{
	public:
		Cgi();
		Cgi(INLINE_NAMESPACE::Request const & request) : _request(request), _file_size(0) {};
		Cgi(const Cgi & copy);

		~Cgi();

		Cgi & operator=(const Cgi & copy);

		void	find_status_code(void);
	private:

		int			_file_size;
		std::string	_status_code;
		INLINE_NAMESPACE::Request		_request;
};

#endif
