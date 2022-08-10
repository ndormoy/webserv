/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:33:04 by mamaurai          #+#    #+#             */
/*   Updated: 2022/08/10 11:04:21 by gmary            ###   ########.fr       */
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
	// CNOUT(UMAG << filename << CRESET)
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

bool
path_is_dir (const std::string & str) {
	struct stat buffer;
	
  	return (stat (str.c_str(), &buffer) == 0 && buffer.st_mode & S_IFDIR);
}

bool
path_is_valid (const std::string & str) {
	struct stat buffer;
	
  	return (stat (str.c_str(), &buffer) == 0);
}

std::string
create_html_error_page (int error_code) {

    std::map<short, std::string> error_pages = webserv::init_error_map();
    std::map<short, std::string>::const_iterator it = error_pages.begin();
    std::string page = "";

    for (; it != error_pages.end(); ++it) {
        if (it->first == error_code)
            break;
    }
    if (it == error_pages.end())
        return ("");

    page += ITOA(error_code) + " " + it->second + "\r\n";
    page += "Content-Type: text/html;charset=UTF-8\r\n";
    page += "Content-Length: " + ITOA(it->second.length() + 127) + "\r\n\n\n";
	
    page += "<!DOCTYPE html>\r\n";
    page += "<html>\r\n";
    page += "<head>\r\n";
    page += "<title>Error " + ITOA(error_code) + "</title>\r\n";
    page += "</head>\r\n";
    page += "<body>\r\n";
    page += "<h1>Error " + ITOA(error_code) + "</h1>\r\n";
    page += "<p>" + it->second + "</p>\r\n";
    page += "</body>\r\n";
    page += "</html>\r\n";
    return page;
}

std::string
remove_slash (const std::string & str) {
    if (str == "/")
        return ("");
    else
        return (str.substr(((str[0] == '/') ? 1 : 0), str.size() - ((str[str.size() - 1] == '/') ? 1 : 0)));
}