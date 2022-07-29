#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Response
{
	public:
		Response();
		Response(Request const & request) :
			_file_size(0),
			_header("HTTP/1.1 "),
			_request(request)
			{};
		Response(const Response & copy) :
			_file_size(copy._file_size),
			_header(copy._header),
			_request(copy._request),
			_files(copy._files){};

		~Response(){};

		Response & operator=(const Response & copy);

		void	fill_status_code(void);
		void 	fill_header(void);
		void 	fill_start_header(void);
		void	fill_body(void);
		void	manage_response(void);
		std::string auto_index(std::string location_path);
		void	create_index(void);
	
	public:
		std::string	get_header() { return _header ; }
		std::string	get_message_send() { return _message_send ; }
		void	set_message_send(std::string message) { _message_send = message; }
	
	private:

		int				_file_size;
		std::string		_header;
		Request			_request;
		string_vector	_files;
		std::string		_error_path;
		std::string		_message_send;
};

_END_NAMESPACE_WEBSERV

#endif
