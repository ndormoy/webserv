#include "../incs/webserv.hpp"
#include <iostream>
#include <fstream>

/*Cette fonction calcule la taille du texte dans un fichier
si le fichier est impossible a ouvrir on affiche une erreur et 
on renvoie -1*/

int calculate_size_file(char *filename)
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

// int main(int argc, char *argv[])
// {
// 	std::cout << "ret = " << calculate_size_file(argv[1]) << std::endl;
// }