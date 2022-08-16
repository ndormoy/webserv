#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Cgi;

class Response
{
	private: /* Attributes */

		int				_file_size;
		std::string		_body;
		std::string		_header; //TODO a enlever
		Request			_request;
		string_vector	_files;
		std::string		_error_path;
		std::string		_message_send;
		int				_error_value;
		Server *		_server;
		Location *		_location;
        Cgi *           _cgi;
		//Header	&		_header;

	public: /* Constructors */

		Response (void) :
			_file_size(0),
			//_header(""),
			_request(),
			_files(),
			_error_path(""),
			_message_send(""),
			_error_value(0),
			_server(_nullptr),
			_location(_nullptr),
            _cgi (_nullptr)
		{ }

		Response (const Request & request) :
			_file_size(0),
			//_header("HTTP/1.1 "),
			_request(request),
			_files(),
			_error_path(""),
			_message_send(""),
			_error_value(request.get_error_value()),
			_server(request.get_server()),
			_location(request.get_location())
		{ }

		Response (const Response & copy) {
			*this = copy;
		}

		~Response (void)
		{ }

	public: /* Accessors */

		int 				get_file_size (void) const 				{ return _file_size; }
		//Header &			get_header (void) const 				{ return _header; }
		Request & 			get_request (void)		 				{ return _request; }
		string_vector & 	get_files  (void)  						{ return _files; }
		std::string 		get_error_path (void) const 			{ return _error_path; }
		std::string 		get_message_send (void) const 			{ return _message_send; }
		int 				get_error_value (void) const 			{ return _error_value; }
		Server * 			get_server (void) const 				{ return _server; }
		Location * 			get_location (void) const 				{ return _location; }
		std::string			get_body (void) const 					{ return _body; }
		std::string			get_cookie(void) const 					{ return _request.get_params("Cookie"); }

		void				set_file_size(int size) 				{ _file_size = size; }
		//void				set_header(std::string header) 			{ _header = header; }
		void				set_request(Request & request) 			{ _request = request; }
		void				set_files(string_vector & files) 		{ _files = files; }
		void				set_error_path(std::string path) 		{ _error_path = path; }
		void				set_message_send(std::string message) 	{ _message_send = message; }
		void				set_error_value(int value) 				{ _error_value = value; }
		void				set_server(Server * server) 			{ _server = server; }
		void				set_location(Location * location) 		{ _location = location; }

	public: /* Functions */

		bool			cookie_exist(void)						{ return _request.params_exist("Cookie"); }
		void			fill_status_code(void);
		void 			fill_header(void);
		void 			fill_start_header(void);
		void			fill_body(void);
		void			manage_response(void);
		void			manage_response_get(void);
		void			manage_response_post(void);
		void			manage_response_delete(void);
		void			manage_response_cgi(void);
		bool			manage_autoindex(void);
		void			manage_error_page(void);
		void			generate_header(void);
		std::string		auto_index(std::string location_path);
		void			create_index(void);
		void			create_upload_file(std::string);
        void            manage_cgi (void);


	public: /* Operators overloaded */

		friend std::ostream& operator<<(std::ostream& o, const Response & ref) {
			o << ref._file_size << std::endl;
			//o << ref._header << std::endl;
			// o << ref._request << std::endl;
			// o << ref._files << std::endl;
			o << ref._error_path << std::endl;
			o << ref._message_send << std::endl;
			o << ref._error_value << std::endl;
			o << ref._server << std::endl;
			o << ref._location << std::endl;
            o << ref._body << std::endl;
			return o;
		}

		Response & operator=(const Response & copy) {
			if (this == &copy) {return (*this);}
			_file_size = copy._file_size;
			//_header = copy._header;
			_request = copy._request;
			// _files = copy._files;
			_error_path = copy._error_path;
			_message_send = copy._message_send;
			_error_value = copy._error_value;
			_server = copy._server;
			_location = copy._location;
			return (*this);
		}

		public: /* Exceptions */
};

_END_NAMESPACE_WEBSERV

#endif
