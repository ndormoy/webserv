/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _location.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:03:56 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/01 16:17:42 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LOCATION_HPP
# define _LOCATION_HPP

#include "_utils.hpp"

_BEGIN_NAMESPACE_WEBSERV

typedef struct s_location
{
	s_location (void) :
		_methods(0),
		_return(),
		_root(""),
		_index(""),
		_autoindex(false),
		_cgi(),
		_upload_path()
	{ }

	~s_location (void)
	{ }

	uint8_t	_methods;
	std::vector<std::pair<int, std::string> > _return;
	std::string	_root;
	std::string _index;
	bool	_autoindex;
	std::string	_cgi;
	std::string _upload_path;
	
}	t_location;

_END_NAMESPACE_WEBSERV

#endif