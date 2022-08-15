/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:43:52 by mamaurai          #+#    #+#             */
/*   Updated: 2022/08/02 15:32:54 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"

void
INLINE_NAMESPACE::Cgi::init_env(void) {
    std::string var_name[] = {
            "CONTENT_LENGTH",
            "CONTENT_TYPE",
            "GATEWAY_INTERFACE",
            "PATH_INFO",
            "PATH_TRANSLATED",
            "QUERY_STRING",
            "REDIRECT_STATUS",
            "REQUEST_METHOD",
            "SCRIPT_FILENAME",
            "SERVER_PROTOCOL",
            "SERVER_PORT",
            ""};

    for (int i = 0; !var_name[i].empty(); i++) {

        // switch (i) {
        // 	case 0:
        // }
    }

    /*
        Init every env variable.
    */
}

int
INLINE_NAMESPACE::Cgi::read_output(int fd) {
    char buffer[BUFFER_SIZE];
    int ret;

    while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0) {
        _output.append(buffer, ret);
    }
    if (ret == SYSCALL_ERR)
        return (SYSCALL_ERR);
    return (0);
}

void
INLINE_NAMESPACE::Cgi::start (void) {

}



