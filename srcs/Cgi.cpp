/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:43:52 by mamaurai          #+#    #+#             */
/*   Updated: 2022/08/16 10:15:57 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"

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
    pid_t pid;
}

void
INLINE_NAMESPACE::Cgi::init (void) {
    string_vector env_vars = create_env();

    if (!(_env = static_cast<char **>(malloc(sizeof(char *) * (env_vars.size() + 1)))))
        return ;
    for (int i = 0; i < env_vars.size(); i++) {
        if (!(_env[i] = static_cast<char *>(malloc(sizeof(char) * (env_vars[i].size() + 1))))) {
            for (int j = 0; j < i; j++)
                free(_env[j]);
            free(_env);
            return ;
        }
        _env[i] = const_cast<char *>(env_vars[i].c_str());
    }
    _env[env_vars.size()] = _nullptr;

    for (int i = 0; _env[i]; i++) {
        CNOUT(BBLU << _env[i] << CRESET);
    }

}

string_vector
INLINE_NAMESPACE::Cgi::create_env (void) const {
    string_vector envs(30);

    envs[0] = "CONTENT_LENGTH=" + ITOA(_request->get_params("Content-Length"));
    envs[1] = "CONTENT_TYPE=" + _request->get_params("Content-Type"); // mostly text/html
    envs[2] = "GATEWAY_INTERFACE=CGI/1.1"; // CGI/1.1
    envs[3] = "PATH_INFO=" + _request->get_path(); // path to the file
    envs[4] = "PATH_TRANSLATED=" + _request->get_path(); // path to the file
    envs[5] = "QUERY_STRING=" + _request->get_query_string(); // ?arg1=value1&arg2=value2
    envs[6] = "REDIRECT_STATUS=" + ITOA(_request->get_error_value()); // mostly 200
    switch (_request->get_method()) {
        case M_GET:
            envs[7] = "REQUEST_METHOD=GET";
            break;
        case M_POST:
            envs[7] = "REQUEST_METHOD=POST";
            break;
        case M_DELETE:
            envs[7] = "REQUEST_METHOD=DELETE";
            break;
        default:
            envs[7] = "REQUEST_METHOD=";
            break;
    }

    envs[8] = "SCRIPT_FILENAME=" + _request->get_construct_path(); // /home/mamaurai/www/index.html
    envs[9] = "SERVER_PROTOCOL=HTTP/1.1"; // usually HTTP/1.1
    envs[10] = "SERVER_PORT=" + ITOA(_request->get_location()->get_server()->get_port()); // 8080 for exemple
    envs[11] = "AUTH_TYPE=Basic";
    envs[12] = "SERVER_NAME=" + _request->get_location()->get_server()->get_server_name();
    envs[13] = "SERVER_SOFTWARE=webserv/beta";
    envs[14] = "HTTP_ACCEPT=" + _request->get_params("Accept"); // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    envs[15] = "HTTP_COOKIE=" + _request->get_params("Cookie");
    envs[16] = "HTTP_ACCEPT_LANGUAGE=" + _request->get_params("Accept-Language"); // Accept-Language: en-US,en;q=0.5
    envs[17] = "HTTP_REFERER=" + _request->get_params("Referer");
    envs[18] = "HTTP_USER_AGENT=" + _request->get_params("User-Agent"); // Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:45.0) Gecko/20100101 Firefox/45.0
    envs[19] = "HTTP_ACCEPT_ENCODING=" + _request->get_params("Accept-Encoding"); // Accept-Encoding: gzip, deflate
    envs[20] = "HTTP_ACCEPT_CHARSET=" + _request->get_params("Accept-Charsets"); // Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
    envs[21] = "DOCUMENT_ROOT=" + _request->get_location()->get_root(); // /home/mamaurai/www
    envs[22] = "REQUEST_URI=" + _request->get_path() + ((!_request->get_query_string().empty()) ? ("?" + _request->get_query_string()) : ""); // /index.html?arg1=value1&arg2=value2
    envs[23] = "UPLOAD_PATH=" + _request->get_location()->get_upload_path(); // /home/mamaurai/www/uploads

    return (envs);
}



