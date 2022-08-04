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
	CNOUT(BYEL << _request.get_path() << CRESET)
	CNOUT(BYEL << _error_path << CRESET)

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
		//_header.append("image/jpeg");
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
	CNOUT(BYEL << _request.get_error_value() << CRESET)
	if (_request.get_error_value() == 200)
	{
		//CNOUT(UMAG << _request.get_path() << CRESET)
		std::string i = ITOA(calculate_size_file((char *)_request.get_path().c_str()));
		_header.append(i);
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

void	INLINE_NAMESPACE::Response::manage_response_delete(void)
{
	//BUG doit on proteger la suppresion du fichier ? si oui qu'elles sont les regles de gestion des droits ?
	if (std::remove(_request.get_path().c_str()) != 0)
	{
		CNOUT(BYEL << "Error deleting file" << CRESET)
		_request.set_error_value(403);
	}
	fill_status_code();
	fill_start_header();
	_header.append("52\r\n"); //TODO recalculer des lignes html en dessous
	_header.append("\r\n");
	_header.append("\n\n");
	_header.append("<html>\n");
	_header.append("<body>\n");
	_header.append("<h1>FILE DELETED</h1>\n");
	_header.append("</body>\n");
	_header.append("</html>\n");
}

void	INLINE_NAMESPACE::Response::manage_response_post(void)
{
	bool	isupload = false;
	std::vector<Location *> location;
	INLINE_NAMESPACE::Server * server = NULL;

	server = _request.get_server();
	if(server != NULL)
	{
		location = server->get_locations();
	}
	else
	{
		CNOUT(BYEL << "server is null" << CRESET)
		return ;
	}
	if (_request.define_upload())
	{
		isupload = true;
	}

	for (std::vector<Location *>::iterator it = location.begin(); it != location.end(); ++it)
	{
		if (!(*it)->get_upload_path().empty())
		{

			isupload = true;
			break;
		}
	}
	//if (_request.get_path().find("upload") != std::string::npos)
	//	isupload = true;
	//if (isupload)
	if (isupload == true)
	{
		_request.set_error_value(200);
		fill_status_code();
		fill_start_header();
		_header.append("53\r\n"); //TODO recalculer des lignes html en dessous
		_header.append("\r\n");
		_header.append("\n\n");
		_header.append("<html>\n");
		_header.append("<body>\n");
		_header.append("<h1>FILE UPLOADED</h1>\n");
		_header.append("</body>\n");
		_header.append("</html>\n");
	}
	else
	{
		_request.set_error_value(500);
		fill_status_code();
		fill_start_header();
		_header.append("57\r\n"); //TODO recalculer des lignes html en dessous
		_header.append("\r\n");
		_header.append("\n\n");
		_header.append("<html>\n");
		_header.append("<body>\n");
		_header.append("<h1>FILE UPLOAD ERROR</h1>\n");
		_header.append("</body>\n");
		_header.append("</html>\n");
	}
}

void	INLINE_NAMESPACE::Response::manage_response_cgi(void)
{

}

/**
 * @brief Search and create autoindex.html file
 */

void	INLINE_NAMESPACE::Response::manage_autoindex(void)
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
							return ;
						}
				}
			}
		}
	}
}

void	INLINE_NAMESPACE::Response::manage_response_get(void)
{

	fill_status_code();
	manage_autoindex();
	fill_header();
	fill_body();
}

void	INLINE_NAMESPACE::Response::manage_response(void)
{
	//TODO faire manage cgi
/* 	if (_request.get_method() == "CGI")
		manage_response_cgi();
	else */ if (_request.get_method() == M_GET)
		manage_response_get();
	else if (_request.get_method() == M_POST)
		manage_response_post();
	else if (_request.get_method() == M_DELETE)
		manage_response_delete();
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
				{

					//CNOUT(UMAG << ep->d_name << CRESET)
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

	fill_start_header();

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
	_header.append(ITOA(len));
	_header.append("\r\n");
	_header.append("\n\n");
	_header.append(index);
	// CNOUT(BYEL << _header << CRESET)
	return index;
}
