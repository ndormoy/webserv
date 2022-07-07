/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:38:48 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/07 16:46:48 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/*
	TODO add _set_server_name in server class
*/



void
INLINE_NAMESPACE::Configuration::parser (void) {
	string_vector::const_iterator it = _lexer.begin();
	
	while (it != _lexer.end()) {
		if (*it == "server" && ((it + 1) != _lexer.end() && (*(it + 1)) == "{")) {
			INLINE_NAMESPACE::Server* s = new Server();
			it += 2;
			s->create_server(it);
			_servers.push_back(s);
		} else {
			throw Configuration::SyntaxError();
		}
		if (it != _lexer.end())
			it++;
	}
}
  
void
INLINE_NAMESPACE::Configuration::lexer (std::string conf_file) {
	std::string 				buffer;
	std::ifstream				ifs;
	string_vector 	v;

	ifs.open(conf_file);
	if (ifs.fail()) {
		throw Configuration::FileCannotBeOpened();
	}
	while (!ifs.eof()) {
		std::getline(ifs, buffer);
		v = vector_spliter(buffer);
		
		if (v.empty() || v[0][0] == '#') {
			continue;
		} else {
			_lexer.insert(_lexer.end(), v.begin(), v.end());
		}
	}
	if (_lexer.empty()) {
		throw Configuration::InvalidFile();
	}
	ifs.close();


}
