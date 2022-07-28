/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:55:35 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/28 16:17:15 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Server {

	public:
		typedef std::vector<std::pair<int, std::string> > 			error_page_type;
		typedef std::vector<Location*>								location_type;
	

	private:
		int 										_port;
		std::string 								_ip;
		size_t 										_max_body_size;
		bool										_default;
		std::string									_server_name;
		error_page_type								_error_pages;
		location_type								_locations;
		

	public:
	
		/**
		 * @brief Construct a new Server object
		 */
		Server (void) :
			_port(0),
			_ip(""),
			_max_body_size(0),
			_default(false),
			_server_name(""),
			_error_pages(),
			_locations()
		{ }
		
		/**
		 * @brief Destroy the Server object
		 */
		virtual ~Server (void) {
			for (location_type::iterator it = _locations.begin(); it != _locations.end(); ++it) {
				delete *it;
			}
			_locations.clear();
			_error_pages.clear();
		}
		
		/**
		 * @brief Construct a new Server object
		 * @param ref The Server object to copy
		 */
		Server (const Server& ref) {
			*this = ref;
		}

		/**
		 * @brief Assign a Server object to another
		 * @param ref The Server object to assign
		 * @return The Server object assigned
		 */
		Server&	operator= (const Server& ref) {
			if (this == &ref) {return (*this);}
			
			_port = ref._port;
			_ip = ref._ip;
			_max_body_size = ref._max_body_size;
			_server_name = ref._server_name;
			_default = ref._default;
			_error_pages = ref._error_pages;
			_locations = ref._locations;
			return (*this);
		}

		// GETTERS

		/**
		 * @brief Get the server port
		 */
		int					get_port (void) const 			{return (_port);}

		/**
		 * @brief Get the server ip
		 */
		std::string			get_ip (void) const 			{return (_ip);}

		/**
		 * @brief Get the server max body size
		 */
		size_t 				get_max_body_size (void) const 	{return (_max_body_size);}

		/**
		 * @brief Get the server name
		 */
		std::string 		get_server_name (void) const 	{return (_server_name);}

		/**
		 * @brief Get the server error pages
		 */
		error_page_type 	get_error_pages (void) const 	{return (_error_pages);}

		/**
		 * @brief Get the server locations
		 */
		location_type 		get_locations (void) const 		{return (_locations);}

		/**
		 * @brief Get the server default setting
		 */
		bool				get_default (void) const 		{return (_default);}

		// FUNCTIONS

		/**
		 * @brief Navigates the vector and stock every server settings
		 * @param Iterator iterator that navigates the lexer
		 */
		void				create_server (string_vector::const_iterator &);

	private:

		/**
		 * @brief Set the server listen port
		 * @param Iterator iterator that navigates the lexer
		 */
		void				_set_port (string_vector::const_iterator &);

		/**
		 * @brief Set the server max body size
		 * @param Iterator iterator that navigates the lexer
		 */
		void				_set_max_body_size (string_vector::const_iterator &);

		/**
		 * @brief Set the server name
		 * @param Iterator iterator that navigates the lexer
		 */
		void				_set_server_name (string_vector::const_iterator &);

		/**
		 * @brief Set the server error pages
		 * @param Iterator iterator that navigates the lexer
		 */
		void				_set_error_page (string_vector::const_iterator &);

		/**
		 * @brief Set the server locations block
		 * @param Iterator iterator that navigates the lexer
		 */
		void				_set_location (string_vector::const_iterator &);
		


	public:

	

		/**
		 * @brief operator overload << for Server class, used mostly with --debug option
		 * 
		 * @param o Output stream
		 * @param s Server object
		 * @return std::ostream& - Output stream
		 */
		friend std::ostream & operator<< (std::ostream & o, const Server & s) {
			CNO("server :", o);
			CNO("port -> " << s._port, o);
			CNO("max_body_size -> " << s._max_body_size, o);
			CNO("server_name -> " << s._server_name, o);
			CNO("default -> " << s._default, o);
			CNO("error pages :", o);
			for (error_page_type::const_iterator it = s._error_pages.begin(); it != s._error_pages.end(); it++) {
				CNO(it->first << " -- " << it->second, o);
			}
			CNO("location :", o);
			for (location_type::const_iterator it = s._locations.begin(); it != s._locations.end(); it++) {
				CO(*(*it), o);
			}
			return (o);
		}		
};

/**
 * @brief Structure used to store a pair of string and Server member function
 */
typedef struct s_function_pair_server {
	void (Server::*f) (string_vector::const_iterator &);
	std::string	str;
}	t_function_pair_server;


_END_NAMESPACE_WEBSERV

#endif /* SERVER_HPP */