/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:09:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/09/15 10:49:22 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

# define KO_SIZE_	1000
# define MO_SIZE_	1000000

void
INLINE_NAMESPACE::Server::_set_port (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);
	int port;
	int ret;

	if ((v.size() == 1 || v.size() == 2) && CHECKER(v, CHECK_PORT | CHECK_DEFAULT)) {
		if ((ret = v[0].find(":")) != std::string::npos) {
			_ip = std::atoll(v[0].substr(0, ret).c_str());
			port = std::atoll(v[0].substr(ret + 1, v[0].length()).c_str());	
		} else {
			port = std::atoll(v[0].c_str());
		}
		_default = (v.size() == 2 ? true : false);
		_port.push_back(port);
	} else {
		throw Configuration::InvalidPort();
	}
}

void
INLINE_NAMESPACE::Server::_set_max_body_size (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);
	
	if (CHECKER(v, CHECK_SIZE_ONE | CHECK_MBS)) {
		if (v[0].find("m") != std::string::npos || v[0].find("M") != std::string::npos) {
			_max_body_size = std::atoll(v[0].substr(0, v[0].length() - 1).c_str()) * MO_SIZE_;
		} else if (v[0].find("k") != std::string::npos || v[0].find("K") != std::string::npos) {
			_max_body_size = std::atoll(v[0].substr(0, v[0].length() - 1).c_str()) * KO_SIZE_;
		} else {
			_max_body_size = std::atoll(v[0].c_str());
		}
	} else {
		throw Configuration::InvalidBodySizeMax();
	}
}

void
INLINE_NAMESPACE::Server::_set_server_name (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);

	if (CHECKER(v, CHECK_SIZE_ONE)) {
		_server_name = v[0];
	} else {
		throw Configuration::InvalidServerName();
	}
}

void
INLINE_NAMESPACE::Server::_set_error_page (string_vector::const_iterator & it) {
	string_vector v = get_until_semicolon(it);

	if (CHECKER(v, CHECK_ERROR_CODE | CHECK_SIZE_TWO | CHECK_CORRECT_PATH)) {
		_error_pages.push_back(std::make_pair(std::atoi(v[0].c_str()), v[1]));
	} else {
		throw Configuration::InvalidErrorPage();
	}
}

void
INLINE_NAMESPACE::Server::_set_location (string_vector::const_iterator & it) {
	
	string_vector v(1, *(it++));
	if (!CHECKER(v, CHECK_IS_DIR))
		throw Configuration::InvalidLocation();
	if (it != LEXER.end() && (*it) == "{") {
		INLINE_NAMESPACE::Location* loc = new Location(v[0]);
		_locations.push_back(loc);
        loc->set_server(this);
		loc->create_location(++it);
	} else {
		throw Configuration::InvalidLocation();
	}
}

void
INLINE_NAMESPACE::Server::create_server (string_vector::const_iterator & it) {
	int idx;
	const t_function_pair_server	pairs[] = {	{&Server::_set_port, "listen"},
										{&Server::_set_max_body_size, "client_max_body_size"},
										{&Server::_set_server_name, "server_name"},
										{&Server::_set_error_page, "error_page"},
										{&Server::_set_location, "location"},
										{NULL, ""} };
	
	while (it != LEXER.end() && *it != "}") {
		for (idx = 0; pairs[idx].f != NULL; idx++) {
			if (*it == pairs[idx].str) {
				++it;
				(this->*pairs[idx].f)(it);
				break;
			}
		}
		if (pairs[idx].str == "") {
			throw Configuration::InvalidKeyword();
		}
		if (it != LEXER.end())
			it++;
	}
	if (it == LEXER.end()) {
		throw Configuration::SyntaxError();
	}
}

std::string
INLINE_NAMESPACE::Server::return_path_matching(int return_code) {
    for (std::vector<std::pair<int, std::string> >::const_iterator it = _error_pages.begin(); it != _error_pages.end(); it++) {
        if (it->first == return_code) {
            return (it->second);
        }
    }
    return ("");
}

