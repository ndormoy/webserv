/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:32:45 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/04 11:24:37 by mamaurai         ###   ########.fr       */
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
	
	public:
		void	parse(std::string);

	public:
		class FileCannotBeOpened : public std::exception {
			public:
				const char * what (void) const throw() {
					return ("configuration_file can't be opened, please check if the file exist and your allowed to open it");
				}
		};
};

_END_NAMESPACE_WEBSERV

#endif
