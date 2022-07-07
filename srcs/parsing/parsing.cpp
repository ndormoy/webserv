/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:09:26 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/07 17:03:29 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

template<typename T>
static typename std::vector<T>::const_iterator
find_ (std::vector<T> & v, T const & value) {
	for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (*it == value) {
			return it;
		}
	}
	return (v.end());
}

static void
remove_comment_ (string_vector & v) {
	string_vector::const_iterator it = v.begin();
	std::string replace;

	for (; it != v.end(); it++) {
		if ((*it).find("#") != std::string::npos) {
			int end = (*it).find("#");
			replace = (*it).substr(0, end);
			v.erase(it, v.end());
			if (!replace.empty())
				v.push_back(replace);
			return;
		}
	}
}

static void
separe_special_char_ (string_vector & v) {
	string_vector::const_iterator it = v.begin();
	std::string	special_char[] = {"{", "}", ";", ""};
	std::string save_s;
	std::string c;
	std::size_t	f_val;

	for (; it != v.end(); it++) {
		f_val = std::string::npos;
		for (int i = 0; special_char[i] != ""; i++) {
			if (*it == special_char[i]) {
				break;
			} else if (((f_val = (*it).find(special_char[i])) != std::string::npos)) {
				c = special_char[i];
				break;
			}
		}
		if (f_val != std::string::npos) {
			save_s = *it;
			if (save_s.substr(f_val + 1, save_s.length()) != "")
				it = v.insert(it, save_s.substr(f_val + 1, save_s.length()));
			it = v.insert(it, c);
			if (save_s.substr(0, f_val) != "")
				it = v.insert(it, save_s.substr(0, f_val));
			v.erase(find_(v, save_s));
			it = v.begin();
		}
	}	
}

string_vector
vector_spliter (std::string str) {
	string_vector vector;
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
	remove_comment_(vector);
	separe_special_char_(vector);
	return (vector);
}

string_vector
get_until_semicolon (string_vector::const_iterator & it) {
	string_vector ret;


	for (; it != LEXER.end(); it++) {
		if ((*it) == ";") {
			break;
		} else {
			ret.push_back(*it);
		}
	}
	return ret;
}