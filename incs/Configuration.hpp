/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:32:45 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/05 10:10:26 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_FILE_HPP
# define CONFIGURATION_FILE_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV


class Configuration {

	typedef typename std::vector<Server> vector_server;

	private :
		vector_server	_servers;

	public:
		Configuration (void)
		{ }
		
		~Configuration (void)
		{ }

	private:
		Configuration (const Configuration & ref) {
			*this = ref;
		}
		
		Configuration &	operator= (const Configuration & ref) {
			if (this ==  &ref) {return (*this);}

			return (*this);
		}

		void	_parse_server (std::ifstream &);
		void	_parse_location (std::ifstream &);

	public:
		void	parse(std::string);

	public:
		friend std::ostream & operator<< (std::ostream & o, const Configuration & c ) { 
        	CO("configuration of webserv", o);
			CO("debug_level = " << g_debug_prog_level, o);
			for (vector_server::const_iterator it = c._servers.begin(); it != c._servers.end(); it++) {
				CO(*it, o);
			}
        	return (o);
    	}

	EXCEPTION(FileCannotBeOpened, "configuration_file can't be opened, please check if the file exist and your allowed to open it")
};

typedef struct s_function_pair_config {
	void (Configuration::*f) (std::ifstream  &);
	std::string	str;
}	t_function_pair_config;

_END_NAMESPACE_WEBSERV

#endif
