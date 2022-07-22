/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:32:45 by mamaurai          #+#    #+#             */
/*   Updated: 2022/07/22 14:30:50 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_FILE_HPP
# define CONFIGURATION_FILE_HPP

#include "webserv.hpp"

_BEGIN_NAMESPACE_WEBSERV

class Configuration {

	typedef std::vector<Server*> server_vector;
	typedef std::vector<std::string> lexer_type;

	private :
		server_vector&	_servers;
		lexer_type&		_lexer;

	public:

		/**
		 * @brief Construct a new Configuration object
		 */
		Configuration (void) :
			_servers(*new server_vector()),
			_lexer(*new lexer_type())
		{ }
		
		/**
		 * @brief Destroy the Configuration object
		 */
		virtual ~Configuration (void) {
			for (server_vector::iterator it = _servers.begin(); it != _servers.end(); ++it) {
				delete *it;
			}
			_servers.clear();
			_lexer.clear();
			delete &_servers;
			delete &_lexer;
		}

	private:
		/**
		 * @brief Construct a new Configuration object
		 * @param ref The Configuration object to copy
		 */
		Configuration (const Configuration & ref) :
			_servers(ref._servers),
			_lexer(ref._lexer)
		{ }
		
		

	public:

		/**
		 * @brief Get the Servers object
		 * @return server_vector&
		 */
		server_vector& 		getServers (void) const {return (_servers);}
		
		/**
		 * @brief Get the Lexer object
		 * @return lexer_type& 
		 */
		lexer_type& 		getLexer (void) const 	{return (_lexer);}

		/**
		 * @brief Read the configuration file, then add every element to the lexer vector
		 * @param filename The filename of the configuration file
		 */
		void	lexer (std::string);

		/**
		 * @brief Parse the lexer vector
		 */
		void	parser (void);

		void	setup (void);

	public:

		/**
		 * @brief operator overload << for Configuation class, used mostly with --debug option
		 * 
		 * @param o Output stream
		 * @param c Configuration object
		 * @return std::ostream& - Output stream
		 */
		friend std::ostream & operator<< (std::ostream & o, const Configuration & c ) { 
        	CNO("configuration of webserv", o);
			CNO("debug_level = " << g_debug_prog_level, o);
			for (server_vector::const_iterator it = c._servers.begin(); it != c._servers.end(); it++) {
				CNO(*(*it), o);
			}
        	return (o);
    	}

	/**
	 * @brief Exception thrown when the configuration file is not valid
	 */

	EXCEPTION(FileCannotBeOpened, "configuration_file can't be opened, please check if the file exist and your allowed to open it")
	EXCEPTION(InvalidFile, "configuration_file : invalid file")
	EXCEPTION(SyntaxError, "configuration_file : syntax error")

	/**
	 * @brief Exception thrown when the server block is invalid
	 */

	EXCEPTION(InvalidPort, "configuration_file : invalid port")
	EXCEPTION(InvalidBodySizeMax, "configuration_file : invalid body size max")
	EXCEPTION(InvalidServerName, "configuration_file : invalid server name")
	EXCEPTION(InvalidErrorPage, "configuration_file : invalid error page")
	EXCEPTION(InvalidLocation, "configuration_file : invalid location")

	/**
	 * @brief Exception thrown when a location block is invalid
	 */

	EXCEPTION(InvalidMethod, "configuration_file : invalid method field")
	EXCEPTION(InvalidRoot, "configuration_file : invalid root field")
	EXCEPTION(InvalidIndex, "configuration_file : invalid index field")
	EXCEPTION(InvalidAutoIndex, "configuration_file : invalid auto index filed")
	EXCEPTION(InvalidUpload, "configuration_file : invalid upload path")
	EXCEPTION(InvalidReturn, "configuration_file : invalid return field")
	EXCEPTION(InvalidCgi, "configuration_file : invalid cgi field")
	EXCEPTION(InvalidKeyword, "configuration_file : invalid keyword")
};

/**
 * @brief Structure used to store a pair of string and Configuration member function
 */
typedef struct s_function_pair_config {
	void (Configuration::*f) (std::ifstream  &);
	std::string	str;
}	t_function_pair_config;

_END_NAMESPACE_WEBSERV

#endif /* CONFIGURATION_FILE_HPP */
