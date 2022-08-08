/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:33:58 by mamaurai          #+#    #+#             */
/*   Updated: 2022/08/08 10:50:58 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UTILS_HPP
# define _UTILS_HPP

class Server;

# define INLINE_NAMESPACE				webserv
#define _BEGIN_NAMESPACE_WEBSERV		namespace INLINE_NAMESPACE {
#define _END_NAMESPACE_WEBSERV 	 		}

# define DEBUG_OPTION					"--debug="
# define DEBUG_LEVEL_MAX					5
# define DEBUG_LEVEL_MIN					0

# define INVALID_ARG					"invalid argument number\n./webserv [--debug=`debug_value`] [configuration_file]"
# define FILE_MISSING					"configuration file missing\n./webserv [--debug=`debug_value`] [configuration_file]"

# define SYSCALL_ERR					(-1)
# define SUCCESS						0

# define COUT(x)						std::cout << x;
# define CO(x, o)						o << x;
# define CERR(x)						std::cerr << x;
# define CNOUT(x)						std::cout << x << std::endl;
# define CNO(x, o)						o << x << std::endl;
# define CNERR(x)						std::cerr << x << std::endl;

# define CONFIG_STRING_MAX_SIZE			100
// TODO before release the project change the number of max_client to 999 and make some tests
# define MAX_CLIENT						4 //BUG which number should we put here, dont put to much if u dont want to fail select()
# define BUFFER_SIZE					1025 // BUG undifined value

# define EXCEPTION(x, y)				public: class x : public std::exception {const char * what (void) const throw() {return (y);}};

# define DEBUG_1(x)						if (g_debug_prog_level >= 1) { x }
# define DEBUG_2(x)						if (g_debug_prog_level >= 2) { x }
# define DEBUG_3(x)						if (g_debug_prog_level >= 3) { x }
# define DEBUG_4(x)						if (g_debug_prog_level >= 4) { x }
# define DEBUG_5(x)						if (g_debug_prog_level >= 5) { x }

# define LEXER							g_config.getLexer()
# define SERVERS						g_config.getServers()
# define HEADER							g_header

# define FOREACH_SERVER					for (std::vector<INLINE_NAMESPACE::Server*>::const_iterator it = SERVERS.begin(); it != SERVERS.end(); ++it)
# define FOREACH_HEADER 				for (string_vector::const_iterator it = HEADER.begin(); it != HEADER.end(); ++it)

# define COUNT_SERVERS					g_config.getServers().size()
# define CHECKER(v, x)					(true == checker(v, x))

// TODO TO DELETE
# define PUT_VECTOR(x)					for (auto it = x.begin(); it != x.end(); it++) { std::cout << *it << " " << std::endl; }  std::cout << std::endl;

# define ITOA( x ) static_cast< const std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

typedef std::vector<std::string> string_vector;

/**
 * @brief Enum used to define different methods
 */
enum {
	M_GET = (1 << 0),
	M_POST = (1 << 1),
	M_DELETE = (1 << 2)
};

/**
 * @brief Structure used to store a pair of flag(std::size_t) and member function
 */
typedef struct s_check {
	bool	(*check)(const string_vector &);
	std::size_t	flag;
} t_check;

/**
 * @brief Enum used to define every checker condition flags
 */
enum {
	CHECK_SIZE_ONE = (1 << 0), // ok
	CHECK_SIZE_TWO = (1 << 1), // ok
	CHECK_CORRECT_PATH = (1 << 2), // ok
	CHECK_IS_DIR = (1 << 3), // ok
	CHECK_METHODS = (1 << 6), // ok
	CHECK_SWITCH_ON = (1 << 7), // ok
	CHECK_EXTENTION = (1 << 8), // ok
	CHECK_MBS = (1 << 10), // ok
	CHECK_PORT = (1 << 11), // ok
	CHECK_ERROR_CODE = (1 << 12), // ok
	CHECK_DEFAULT = (1 << 13), // ok
	CHECK_IS_REG = (1 << 14), // ok
};


/**
 * @brief Split the string in a vector of string
 * 
 * @param str original string
 * @param delim list of delimiters to split the string
 * @param to_del list of character to delete from the string
 * @return string_vector 
 */
string_vector	vector_spliter (std::string str, const char *, const char *, bool);

/**
 * @brief Return a bool to know if the string is printable 
 * 
 * @param str String to check
 * @return bool true = is_printable, false = not_printable
 */
bool						str_is_print(std::string str);

/**
 * @brief Copy and increment the iterator until found out a string ending with semicolon
 * 
 * @param it Iterator that navigates the lexer
 * @return string_vector new vector of string
 */
string_vector				get_until_semicolon (string_vector::const_iterator & it);

/**
 * @brief Apply multiple tests on a string_vector to know if the configuration is correct
 * 
 * @param v Vector of the strings that follow the option
 * @param flags Settings to check
 * @return bool - true if all tests are successful 
 */
bool						checker(const string_vector & v, std::size_t flags);

/**
 * @brief Return the size of the file given by the path, -1 if the file could not be opened
 * 
 * @param filename 
 * @return int - size of the file
 */
int							calculate_size_file (char *filename);

/**
 * @brief Return if str is a HTTP header
 * 
 * @param str 
 * @return bool - true if the string is a HTTP header
 */
bool						is_header (const std::string & str);

/**
 * @brief Return if the file exist and can be opened
 * 
 * @param path 
 * @return bool - true if the file exist
 */
inline bool					file_exist (const std::string & path) {
	struct stat buffer;   
	return (stat (path.c_str(), &buffer) == 0 && buffer.st_mode & S_IFREG); 
}

/**
 * @brief Return a string with the content of a file
 * 
 * @param path
 * @return string content of the file
 */

std::string					read_file(std::string path);

/**
 * @brief Return if a path is a directory or not
 * 
 * @param str path
 * @return bool - true if the file exist and is a directory
 */
bool						path_is_dir (const std::string & str);

bool						path_is_valid (const std::string & str);

#endif /* _UTILS_HPP */