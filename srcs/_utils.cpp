/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:33:04 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/26 09:23:45 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

bool
str_is_print (std::string str) {
	const char *s = str.c_str();
	
	for (size_t i = 0; i < str.length(); i++) {
		if (!isprint(s[i]))
			return (false);
	}
	return (true);
}


int
calculate_size_file (char *filename)
{
	std::streampos begin,end;
	std::ifstream myfile (filename, std::ios::binary);
	if (myfile.is_open())
	{
		begin = myfile.tellg();
		myfile.seekg (0, std::ios::end);
		end = myfile.tellg();
		myfile.close();
		//std::cout << "size is: " << (end-begin) << " bytes.\n";
	}
	else
	{
		std::cerr << BRED << "Unable to open file" << CRESET << std::endl;
		return (-1);
	}
	return (end - begin);
}

//BUG surement a tej pb merge 
bool
is_header (const std::string & str) {

	FOREACH_HEADER {
		// CNOUT("HEEEEEEEEEEEEEEERE" << *it);
		if (str == *it)
			return (true);
	}
	return (false);
}

std::string	read_file(std::string path)
{
	std::string content = "";
	std::ifstream file(path.c_str());
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
			content += line + "\n";
		file.close();
	}
	else
		content = "Problem reading file";
	return content;
}
