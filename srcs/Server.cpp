/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:09:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/05 09:23:34 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void
INLINE_NAMESPACE::Server::_set_server_name (std::vector<std::string> &v) {
	if (v.size() != 2 || v[1].length() > CONFIG_STRING_MAX_SIZE) {
		throw Server::InvalidServerName();
	} else {
		_server_name = v[1];
	}
}

void
INLINE_NAMESPACE::Server::_set_listen (std::vector<std::string> &v) {
	if (v.size() != 2
		|| v[1].length() > 5
		|| v[1].find_first_not_of("0123456789") != std::string::npos
		|| atoi(v[1].c_str()) > 65535) {
		throw (Server::InvalidPort());
	} else {
		_port = atoi(v[1].c_str());
	}
}

