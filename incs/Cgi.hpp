/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:06:23 by mamaurai          #+#    #+#             */
/*   Updated: 2022/09/21 12:49:35 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "webserv.hpp"
# include "Response.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Response;

class Cgi
{
	private:
		char ** 	_env;
		std::string _exec;
		std::string _extension;
		int			_fd;
		Request *	_request;
		Location * 	_location;
		std::string _output;
        std::map<std::string, std::string> _params;

	public:
		Cgi (void) :
			_env(NULL),
			_exec(""),
			_extension(""),
			_fd(-1),
			_request(NULL),
			_location(NULL),
			_output(""),
            _params()
		{
            _params["Set-Cookie"] = "";
        }

		virtual ~Cgi (void)
		{ }

		Cgi (Request & request) :
			_env(NULL),
			_exec(""),
			_extension(""),
			_fd(-1),
			_request(&request),
			_location(request.get_location()),
			_output(""),
            _params()
		{
            _params["Set-Cookie"] = "";
        }

        Cgi (const std::string & ext, const std::string & path, Location * loc, Request * req) :
            _env(NULL),
            _exec(path),
            _extension(ext),
            _fd(-1),
            _request(req),
            _location(loc),
            _output(""),
            _params()
        {
            _params["Set-Cookie"] = "";
        }

		Cgi (const Cgi & copy) {
			*this = copy;
		}

	public:

		void				set_env (char ** env) 					{ _env = env; }
		void				set_exec (std::string exec) 			{ _exec = exec; }
		void				set_extension (std::string extension) 	{ _extension = extension; }
		void				set_fd (int fd) 						{ _fd = fd; }
		void				set_request (Request * request) 		{ _request = request; }
		void				set_location (Location * location) 		{ _location = location; }
		void				set_output (std::string output) 		{ _output = output; }


		char ** 			get_env (void) const 					{ return _env; }
		std::string 		get_exec (void) const 					{ return _exec; }
		std::string 		get_extension (void) const 				{ return _extension; }
		int					get_fd (void) const 					{ return _fd; }
		Request *			get_request (void) const 				{ return _request; }
		Location *			get_location (void) const 				{ return _location; }
		std::string 		get_output (void) const 				{ return _output; }
        std::string         get_param (std::string key) const       { return _params.at(key); }

		void				clear (void) {
			_env = NULL;
			_exec = "";
			_extension = "";
			_fd = -1;
			_request = NULL;
			_location = NULL;
			_output = "";
            _params.clear();
		}

	public:

		int 				read_output (int);
        void				start (Response *);
        void				init (void);
        string_vector		create_env (void) const;
        void				manage_output (Response *);
        void				wait (Response *);
		void				free_env(void);
	public:

		friend std::ostream& operator << (std::ostream& o, const Cgi & ref) {
			for (int i = 0; ref._env && ref._env[i]; i++) {
				o << ref._env[i] << std::endl;
			}
			o << ref._exec << std::endl;
			o << ref._extension << std::endl;
			o << ref._fd << std::endl;
			o << ref._request << std::endl;
			o << ref._location << std::endl;
			o << ref._output << std::endl;
            for (std::map<std::string, std::string>::const_iterator it = ref._params.begin(); it != ref._params.end(); ++it) {
                o << it->first << "=" << it->second << std::endl;
            }
			return (o);
		}

		Cgi & operator= (const Cgi & copy) {
			if (this == &copy) {return (*this);}

			_env = copy._env;
			_exec = copy._exec;
			_extension = copy._extension;
			_fd = copy._fd;
			_request = copy._request;
			_location = copy._location;
			_output = copy._output;
            _params = copy._params;

			return (*this);
		}
};

_END_NAMESPACE_WEBSERV

#endif
