/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:38:48 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/04 15:32:28 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/*
	TODO add _set_server_name in server class
*/

#define NBR_DIFFERENT_BLOCKS_	2

static std::vector<std::string>
vector_spliter_ (std::string str) {
	std::vector<std::string> vector;
	std::string stockage;

	std::replace( str.begin(), str.end(), '\t', ' '); 
    int start = 0U;
    int end = str.find(' ');
    while (end != std::string::npos)
    {
		stockage = str.substr(start, end - start);
		if (!stockage.empty())
			vector.push_back(stockage);
        start = end + 1;
        end = str.find(' ', start);
    }

    stockage = str.substr(start, end);
	if (!stockage.empty())
			vector.push_back(stockage);

	return (vector);
}

void
INLINE_NAMESPACE::Configuration::_set_server_name (std::vector<std::string> v) {
	if (v.size() != 2 || v[1].length() > CONFIG_STRING_MAX_SIZE) {
		throw Configuration::InvalidServerName();
	} else {
		
	}
}

void
INLINE_NAMESPACE::Configuration::_parse_server (std::ifstream &ifs) {
	std::string 				buffer;
	std::vector<std::string> 	v;
	t_function_vector pairs[2] = {	{&Configuration::_set_server_name, "server_name"},
									{&Configuration::_set_server_name, "listen"},
									{&Configuration::_set_server_name, "error_page"},
									{&Configuration::_set_server_name, "client_max_body_size"},};
	INLINE_NAMESPACE::Server server;


	while (!ifs.eof()) {
		std::getline(ifs, buffer);
		v = vector_spliter_(buffer);

		for (int i = 0; i < 2; i++) {
			if (v.empty()) {
				continue;
			} else if (v[0] == pairs[i].str) {
				(this->*(pairs[i].f))(ifs);
			}
		}
	}
}

void
INLINE_NAMESPACE::Configuration::_parse_location (std::ifstream &ifs) {
	COUT("location");
}


void
INLINE_NAMESPACE::Configuration::parse (std::string conf_file) {
	std::string 				buffer;
	std::ifstream				ifs;
	std::vector<std::string> 	v;
	t_function_stream pairs[NBR_DIFFERENT_BLOCKS_] = {{&Configuration::_parse_server, "server"},
													{&Configuration::_parse_location, "location"}};
	
	ifs.open(conf_file);
	if (ifs.fail()) {
		throw Configuration::FileCannotBeOpened();
	}

	while (!ifs.eof()) {
		std::getline(ifs, buffer);
		v = vector_spliter_(buffer);

		for (int i = 0; i < NBR_DIFFERENT_BLOCKS_; i++) {
			if (v.empty()) {
				continue;
			} else if (v[0] == pairs[i].str) {
				(this->*(pairs[i].f))(ifs);
			}
		}
	}
}