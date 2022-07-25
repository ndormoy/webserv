#include "../incs/webserv.hpp"
#include <iostream>
#include <fstream>

/*Cette fonction calcule la taille du texte dans un fichier
si le fichier est impossible a ouvrir on affiche une erreur et 
on renvoie -1*/

int Cgi::calculate_size_file(char *filename)
{
	std::streampos begin,end;
	std::ifstream myfile (filename, std::ios::binary);
	if (myfile.is_open())
	{
		begin = myfile.tellg();
		myfile.seekg (0, std::ios::end);
		end = myfile.tellg();
		myfile.close();
	}
	else
	{
		std::cerr << BRED << "Unable to open file" << CRESET << std::endl;
		return (-1);
	}
	return (end - begin);
}

void	Cgi::find_status_code(void)
{
	_file_size = calculate_size_file((char *)_request.get_path().c_str());
	if (_file_size == -1)
		_status_code = "404 Not Found";
	else
		_status_code = "200 OK";

}