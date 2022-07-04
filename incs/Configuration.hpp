/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:32:45 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/04 15:28:40 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_FILE_HPP
# define CONFIGURATION_FILE_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV


class Configuration {

	private :
		std::vector<Server>	_servers;

	public:
		Configuration (void)
		{ }
		
		~Configuration (void)
		{ }

	private:
		Configuration (const Configuration& ref) {
			*this = ref;
		}
		
		Configuration&	operator= (const Configuration& ref) {
			if (this == &ref) {return (*this);}

			return (*this);
		}

		void	_parse_server (std::ifstream&);
		void	_parse_location (std::ifstream&);

		void	_set_server_name (std::vector<std::string>);
		void	_set_listen (std::vector<std::string>);
		void	_set_error_page (std::vector<std::string>);
		void	_set_client_max_body_size (std::vector<std::string>);
	
	public:
		void	parse(std::string);

	public:
		class FileCannotBeOpened : public std::exception {
			public:
				const char * what (void) const throw() {
					return ("configuration_file can't be opened, please check if the file exist and your allowed to open it");
				}
		};

		class InvalidServerName : public std::exception {
			public:
				const char * what (void) const throw() {
					return ("configuration_file : invalid server_name");
				}
		};
};

typedef struct s_function_stream {
	void (Configuration::*f) (std::ifstream &);
	std::string	str;
}	t_function_stream;

typedef struct s_function_vector {
	void (Configuration::*f) (std::ifstream &);
	std::string	str;
}	t_function_vector;

_END_NAMESPACE_WEBSERV

#endif
