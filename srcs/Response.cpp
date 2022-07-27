#include "../incs/webserv.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>

/*Cette fonction calcule la taille du texte dans un fichier
si le fichier est impossible a ouvrir on affiche une erreur et 
on renvoie -1*/


void	INLINE_NAMESPACE::Response::fill_status_code(void)
{
	_file_size = calculate_size_file((char *)_request.get_path().c_str());
	if (_request.get_error_value() == 200)
		_header.append("200 OK\r\n");
	else if (_request.get_error_value() == 400)
		_header.append("400 Bad Request\r\n");
	else if (_request.get_error_value() == 403)
		_header.append("403 Forbidden\r\n");
	else if (_request.get_error_value() == 404)
		_header.append("404 Not Found\r\n");
	else if (_request.get_error_value() == 500)
		_header.append("500 Internal Server Error\r\n");
	else if (_request.get_error_value() == 505)
		_header.append("505 HTTP Version Not Supported\r\n");

}

void		INLINE_NAMESPACE::Response::fill_body(void)
{
	if (_request.get_error_value() == 200)
		_header.append(read_file(_request.get_path()));
	else
		_header.append(read_file(_error_path));
	_header.append("\r\n\r\n");
}

void 	INLINE_NAMESPACE::Response::fill_start_header(void)
{
	_header.append("Content-Type: ");
	// CNOUT(BRED << _request << CRESET)
	// CNOUT(BRED << _request.get_content_type() << CRESET)
	//TODO reactiver tout ce qui est grise dans cette fonction
	//if (_request.get_content_type().empty())
	//{
		_header.append("text/html;charset=UTF-8");
	//}
	//else
	//{
		//CNOUT(BRED << "0B" << CRESET)
		//_header.append(_request.get_content_type());
	//}
	_header.append("\r\n");
	_header.append("Content-Length: ");
}

void		INLINE_NAMESPACE::Response::fill_header(void)
{
	// _header.append("Content-Type: ");
	// if (_request.get_content_type().empty())
	// 	_header.append("text/html;charset=UTF-8");
	// else
	// 	_header.append(_request.get_content_type());
	// _header.append("\r\n");
	// _header.append("Content-Length: ");
	fill_start_header();
	if (_request.get_error_value() == 200)
	{
		_header.append(ITOA(calculate_size_file((char *)_request.get_path().c_str())));
	}
	else
	{
		_error_path = "./www/error_pages/";
		_error_path.append(ITOA(_request.get_error_value()));
		_error_path.append(".html");
		_header.append(ITOA(calculate_size_file((char *)_error_path.c_str())));
	}
	_header.append("\r\n");
	_header.append("\n\n");
}

static INLINE_NAMESPACE::Server *
find_server (const INLINE_NAMESPACE::Request & request) {
	std::string port;
	int ret = request.get_params()["Host:"].find(":");

	if (request.get_params()["Host:"].empty()) {
		return (NULL);
	}
	port = request.get_params()["Host:"].substr(ret + 1, request.get_params()["Host:"].length());
	for (std::vector<INLINE_NAMESPACE::Server*>::iterator it = SERVERS.begin(); it != SERVERS.end(); ++it) {
		if ((*it)->get_port() == std::stoll(port))
		{
			CNOUT("STARFFFF" << *it << " port: " << (*it)->get_port())
			return (*it);
		}
	}
	return (NULL);
} 

void	INLINE_NAMESPACE::Response::manage_response(void)
{
	INLINE_NAMESPACE::Server * server = NULL;
	std::vector<Location *> location;
	fill_status_code();

	// CNOUT(BGRN << *server << CRESET)
	//if (server == NULL)
	//{
	//	CNOUT(BGRN << "\n server is null" << CRESET)
	//	return ;
	//}
	if (_request.get_error_value() != 200)
	{
		CNOUT(GRN << "ERROR" << CRESET)
		server = find_server(_request);
		if (server != NULL)
		{
			CNOUT(GRN << "server is not null" << CRESET)
			location =  server->get_locations();
			if (location.empty() == false)
			{
				CNOUT(GRN << "location not empty" << CRESET)
				for (std::vector<Location *>::iterator it = location.begin(); it != location.end(); it++)
				{
					if ((*it)->get_path() == _request.get_path())
						if ((*it)->get_autoindex() == true)
						{
							CNOUT(BGRN << "autoindex" << CRESET)
							auto_index();
							return ;
						}
				}
			}
		}
	}
	CNOUT(BRED << "AFTER" << CRESET)
	fill_header();
	fill_body();
}

/*Cette fonction permet de regarder dans le repertoire courant (Et ceux d'apres
si on clique dessus), et d'ajouter dans une liste les nom des fichiers
et dossiers presents*/

void	INLINE_NAMESPACE::Response::create_index(void)
{
	DIR *dp;
	struct dirent *ep;

	dp = opendir (_request.get_path().c_str());
	if (dp != NULL)
	{
		while ((ep = readdir (dp)))
		{
			if (ep->d_type == DT_DIR || ep->d_type == DT_LNK
				|| ep->d_type == DT_REG || ep->d_type == DT_UNKNOWN)
				_files.push_back(ep->d_name);
		}
		(void) closedir (dp);
	}
	else
		std::cerr << "Couldn't open the directory" << std::endl;
}

/*Permet de mettre dans une string en html les fichiers/dossier
du repertoire courant, pour pouvoir les afficher en reponse
c'est l'auto index*/

std::string	INLINE_NAMESPACE::Response::auto_index(void)
{
	std::string index;
	int	 		len;

	fill_start_header();

	index += "<html>";
	index += "<head><title>Indexito /</title></head>";
	index += "<body bgcolor=\"green\">";
	index += "<h1>Index of </h1><hr><pre><a href=\"../\">../</a>";
	for (string_vector::iterator it = _files.begin(); it != _files.end(); ++it)
	{
		index += "<a href=\"";
		index += *it;
		index += "\">" "</a>";
		index += "</pre><hr></body>";
	}
	index += "</html>";
	len = index.length();
	_header.append(ITOA(len));
	_header.append("\r\n");
	_header.append("\n\n");
	_header.append(index);
	return index;
}