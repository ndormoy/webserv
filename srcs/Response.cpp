#include "../incs/webserv.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>

/*
	curl -X DELETE localhost:8080/file_to_delete/text.txt
*/

void	INLINE_NAMESPACE::Response::manage_response_delete(void)
{
	//BUG doit on proteger la suppresion du fichier ? si oui qu'elles sont les regles de gestion des droits ?
	if (std::remove(_request.get_construct_path().c_str()) != 0)
	{
		CNOUT(BYEL << "Error deleting file" << CRESET)
		_request.set_error_value(403);
	}
	if (_request.get_error_value() == 200)
	{
		_body.append("<html>\n");
		_body.append("<body>\n");
		_body.append("<h1>FILE DELETED</h1>\n");
		_body.append("</body>\n");
		_body.append("</html>\n");
	}
	else
		_body.append(create_html_error_page(_request.get_error_value()));
}

/**
 * @brief function that create the file were the content of a file is stored
 * std::ifstream automatically has the ios::in flag set.
 * std::ofstream automatically has the ios::out flag set.
 * std::fstream has neither ios::in or ios::out automatically
 * @param upload_path 
 */

void	INLINE_NAMESPACE::Response::create_upload_file(std::string upload_path)
{
	std::ofstream	file;
	std::string		final_path = upload_path;

	final_path.append("/");
	final_path.append(_request.get_filename());
	if (upload_path.empty())
		file.open(("example_html/uploads/" + _request.get_filename()).c_str(), std::ios::out | std::ios::binary);
	else
		file.open(final_path.c_str(), std::ios::out | std::ios::binary);
	file << _request.get_content_file();
	file.close();
}

void	INLINE_NAMESPACE::Response::manage_response_post(void)
{
	bool	isupload = false;
	std::vector<Location *> location;
	INLINE_NAMESPACE::Server * server = NULL;

	server = _request.get_server();
	if(server != NULL)
		location = server->get_locations();
	else
	{
		CNOUT(BYEL << "server is null" << CRESET)
		return ;
	}
	if (_request.define_upload())
		isupload = true;
	else
	{
		//TODO que faire vraiment ici on est ps dans un cas d'upload mais ca peut etre autres choses ??
		isupload = false;
	}
	for (std::vector<Location *>::iterator it = location.begin(); it != location.end(); ++it)
	{
		if (!(*it)->get_upload_path().empty() && isupload)
		{
			if (server->get_max_body_size() < _request.get_content_file().size())
			{
				CNOUT(BRED << "max body size hit" << CRESET)
				_request.set_error_value(413);
				isupload = false;
				break ;
			}
			create_upload_file((*it)->get_upload_path());
			break;
		}
	}
	if (isupload == true)
	{
		_request.set_error_value(200);
		_body.append("53\r\n");
		_body.append("\r\n");
		_body.append("\n\n");
		_body.append("<html>\n");
		_body.append("<body>\n");
		_body.append("<h1>FILE UPLOADED</h1>\n");
		_body.append("</body>\n");
		_body.append("</html>\n");
	}
	else
		_body.append(create_html_error_page(_request.get_error_value()));
}

// void	INLINE_NAMESPACE::Response::manage_response_cgi(void)
// {

// }

/**
 * @brief Search and create autoindex.html file
 */

bool	INLINE_NAMESPACE::Response::manage_autoindex(void)
{
	INLINE_NAMESPACE::Server * server = NULL;
	std::vector<Location *> location;

	if (_request.get_error_value() != 200)
	{
		CNOUT(GRN << "ERROR" << CRESET)
		server = _request.get_server();
		//server = find_server(_request);
		if (server != NULL)
		{
			CNOUT(GRN << "server is not null" << CRESET)
			location =  server->get_locations();
			//TODO check si location a comme option / (tout les dossier son apte a l'autoindex)
			if (location.empty() == false)
			{
				CNOUT(GRN << "location not empty" << CRESET)
				for (std::vector<Location *>::iterator it = location.begin(); it != location.end(); it++)
				{
					if ((*it)->get_path() == _request.get_path())
						if ((*it)->get_autoindex() == true)
						{
							CNOUT(BGRN << "autoindex" << CRESET)
							create_index();
							auto_index((*it)->get_path());
							return true;
						}
				}
			}
		}
	}
	return false;
}

void	INLINE_NAMESPACE::Response::manage_response_get(void)
{
    _body.append(read_file(_request.get_construct_path()));
	_body.append("\r\n\r\n");
	// else if (_location->get_return())
	// else
	// 	_header.append(create_html_error_page(_request.get_error_value()));
}

void
INLINE_NAMESPACE::Response::manage_error_page (void) {
    std::string ret;

    if (_location
        && _error_value == 403
        && _location->get_autoindex()
        && (path_is_dir(_request.get_construct_path())) || _request.get_construct_path().empty()) {
        create_index();
        _body = auto_index(_request.get_path());
    }
    else if (!(ret = _location->return_path_matching(_error_value)).empty()) {
        _body.append(read_file(ret));
    } else {
        _body.append(create_html_error_page(_request.get_error_value()));
    }
}

void	INLINE_NAMESPACE::Response::manage_response(void)
{
	//TODO faire manage cgi
	if (_error_value != 200)
	{
		CCOUT(BGRN, _error_value)
		CCOUT(BRED, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
		manage_error_page();
	}
	else
	{
		CCOUT(BGRN, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
		if (_request.get_method() == M_GET)
			manage_response_get();
		else if (_request.get_method() == M_POST)
			manage_response_post();
		else if (_request.get_method() == M_DELETE)
			manage_response_delete();
	}
	/* 	if (_request.get_method() == "CGI")
			manage_response_cgi(); */
	Header header;
	header.fill(*this);
	CCOUT(BRED, header.get_header())
	//CCOUT(BGRN, _body)
	_body.insert(0, header.get_header());
	CCOUT(BYEL, _body)

// generate header
// concat body
}


















/*Cette fonction permet de regarder dans le repertoire courant (Et ceux d'apres
si on clique dessus), et d'ajouter dans une liste les nom des fichiers
et dossiers presents*/

void	INLINE_NAMESPACE::Response::create_index(void)
{
	DIR *dp;
	struct dirent *ep;
	
	dp = opendir (_request.get_construct_path().c_str());
	if (dp != NULL)
	{
		while ((ep = readdir (dp)))
		{
			if (ep->d_type == DT_DIR || ep->d_type == DT_LNK
				|| ep->d_type == DT_REG || ep->d_type == DT_UNKNOWN)
				{
					_files.push_back(ep->d_name);
				}
		}
		(void) closedir (dp);
	}
	else
		std::cerr << "Couldn't open the directory" << std::endl;
}

/*Permet de mettre dans une string en html les fichiers/dossier
du repertoire courant, pour pouvoir les afficher en reponse
c'est l'auto index*/

std::string	INLINE_NAMESPACE::Response::auto_index(std::string location_path)
{
	std::string index;
	int	 		len;

	//fill_start_header();
	index += "<html>\n";
	index += "<head><title>Indexito /</title></head>\n";
	index += "<body bgcolor=\"green\">\n";
	index += "<h1>Index of </h1><hr><pre><a href=\"../\">../</a>\n";
	for (string_vector::iterator it = _files.begin(); it != _files.end(); ++it)
	{
		index += "<a href=\"";
		index += location_path;
		index += "/";
		index += *it;
		index += "\">";
		index += *it;
		index += "</a>\n";
		index += "</pre><hr>\n";
	}
	index += "</body>\n</html>\n";
	len = index.length();
	//_header.append(ITOA(len));
	//_header.append("\r\n");
	//_header.append("\n\n");
	_body.append(index);
	_body.append("\r\n\r\n");
	return index;
}


void
INLINE_NAMESPACE::Response::generate_header(void)
{

}

/*

Check error value
if (1)
{
	fill body
}
} else {
	fill body;
}
cgi sur _body

generate header
concat body
*/