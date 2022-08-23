/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:06:42 by gmary             #+#    #+#             */
/*   Updated: 2022/08/15 17:04:12 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/webserv.hpp"

string_vector
INLINE_NAMESPACE::init_header(void) {
    string_vector header(20);

    header.push_back("Accept-Charsets");
    header.push_back("Accept-Language");
    header.push_back("Auth-Scheme");
    header.push_back("Authorization");
	header.push_back("Cookie");
    header.push_back("Content-Language");
    header.push_back("Content-Length");
    header.push_back("Content-Location");
    header.push_back("Content-Type");
    header.push_back("Date");
    header.push_back("Host");
    header.push_back("Last-Modified");
    header.push_back("Location");
    header.push_back("Referer");
    header.push_back("Retry-After");
    header.push_back("Transfer-Encoding");
    header.push_back("User-Agent");
    header.push_back("Connection");
    header.push_back("Accept");
    header.push_back("Cookie");
    header.push_back("Accept-Encoding");
    header.push_back("From");
    header.push_back("Cookie");

    return (header);
}

std::map<short, std::string>
INLINE_NAMESPACE::init_error_map(void) {
    std::map<short, std::string> error_map;

    error_map[100] = "Continue";
    error_map[101] = "Switching Protocols";
    error_map[102] = "Processing";
    error_map[103] = "Checkpoint";
    error_map[200] = "OK";
    error_map[201] = "Created";
    error_map[202] = "Accepted";
    error_map[203] = "Non-Authoritative Information";
    error_map[204] = "No Content";
    error_map[205] = "Reset Content";
    error_map[206] = "Partial Content";
    error_map[207] = "Multi-Status";
    error_map[208] = "Already Reported";
    error_map[300] = "Multiple Choices";
    error_map[301] = "Moved Permanently";
    error_map[302] = "Found";
    error_map[303] = "See Other";
    error_map[304] = "Not Modified";
    error_map[305] = "Use Proxy";
    error_map[306] = "Switch Proxy";
    error_map[307] = "Temporary Redirect";
    error_map[308] = "Permanent Redirect";
    error_map[400] = "Bad Request";
    error_map[401] = "Unauthorized";
    error_map[402] = "Payment Required";
    error_map[403] = "Forbidden";
    error_map[404] = "Not Found";
    error_map[405] = "Method Not Allowed";
    error_map[406] = "Not Acceptable";
    error_map[407] = "Proxy Authentication Required";
    error_map[408] = "Request Timeout";
    error_map[409] = "Conflict";
    error_map[410] = "Gone";
    error_map[411] = "Length Required";
    error_map[412] = "Precondition Failed";
    error_map[413] = "Payload Too Large";
    error_map[414] = "URI Too Long";
    error_map[415] = "Unsupported Media Type";
    error_map[416] = "Requested Range Not Satisfiable";
    error_map[417] = "Expectation Failed";
    error_map[418] = "I'm a teapot";
    error_map[421] = "Misdirected Request";
    error_map[422] = "Unprocessable Entity";
    error_map[423] = "Locked";
    error_map[424] = "Failed Dependency";
    error_map[426] = "Upgrade Required";
    error_map[428] = "Precondition Required";
    error_map[429] = "Too Many Request";
    error_map[431] = "Request Header Fields Too Large";
    error_map[451] = "Unavailable For Legal Reasons";
    error_map[500] = "Internal Server Error";
    error_map[501] = "Not Implemented";
    error_map[502] = "Bad Gateway";
    error_map[503] = "Service Unavailable";
    error_map[504] = "Gateway Timeout";
    error_map[505] = "HTTP Version Not Supported";
    error_map[506] = "Variant Also Negotiates";
    error_map[507] = "Insufficient Storage";
    error_map[508] = "Loop Detected";
    error_map[510] = "Not Extended";
    error_map[511] = "Network Authentication Required";

    return (error_map);
}

std::map<std::string, std::string>
INLINE_NAMESPACE::init_content_type() {

    std::map<std::string, std::string> content_map;

    content_map[".aac"] = "audio/aac";
    content_map[".abw"] = "application/x-abiword";
    content_map[".arc"] = "application/octet-stream";
    content_map[".avi"] = "video/x-msvideo";
    content_map[".azw"] = "application/vnd.amazon.ebook";
    content_map[".bin"] = "application/octet-stream";
    content_map[".bz"] = "application/x-bzip";
    content_map[".bz2"] = "application/x-bzip2";
    content_map[".csh"] = "application/x-csh";
    content_map[".css"] = "text/css";
    content_map[".csv"] = "text/csv";
    content_map[".doc"] = "application/msword";
    content_map[".epub"] = "application/epub+zip";
    content_map[".gif"] = "image/gif";
    content_map[".htm"] = "text/html";
    content_map[".html"] = "text/html";
    content_map[".php"] = "text/html";
    content_map[".ico"] = "image/x-icon";
    content_map[".ics"] = "text/calendar";
    content_map[".jar"] = "Temporary Redirect";
    content_map[".jpeg"] = "image/jpeg";
    content_map[".jpg"] = "image/jpeg";
    content_map[".js"] = "application/js";
    content_map[".json"] = "application/json";
    content_map[".mid"] = "audio/midi";
    content_map[".midi"] = "audio/midi";
    content_map[".mpeg"] = "video/mpeg";
    content_map[".mp4"] = "video/mp4";
    content_map[".mpkg"] = "application/vnd.apple.installer+xml";
    content_map[".odp"] = "application/vnd.oasis.opendocument.presentation";
    content_map[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    content_map[".odt"] = "application/vnd.oasis.opendocument.text";
    content_map[".oga"] = "audio/ogg";
    content_map[".ogv"] = "video/ogg";
    content_map[".ogx"] = "application/ogg";
    content_map[".png"] = "image/png";
    content_map[".pdf"] = "application/pdf";
    content_map[".ppt"] = "application/vnd.ms-powerpoint";
    content_map[".rar"] = "application/x-rar-compressed";
    content_map[".rtf"] = "application/rtf";
    content_map[".sh"] = "application/x-sh";
    content_map[".svg"] = "image/svg+xml";
    content_map[".swf"] = "application/x-shockwave-flash";
    content_map[".tar"] = "application/x-tar";
    content_map[".tif"] = "image/tiff";
    content_map[".tiff"] = "image/tiff";
    content_map[".ttf"] = "application/x-font-ttf";
    content_map[".txt"] = "text/plain";
    content_map[".vsd"] = "application/vnd.visio";
    content_map[".wav"] = "audio/x-wav";
    content_map[".weba"] = "audio/webm";
    content_map[".webm"] = "video/webm";
    content_map[".webp"] = "image/webp";
    content_map[".woff"] = "application/x-font-woff";
    content_map[".xhtml"] = "application/xhtml+xml";
    content_map[".xls"] = "application/vnd.ms-excel";
    content_map[".xml"] = "application/xml";
    content_map[".xul"] = "application/vnd.mozilla.xul+xml";
    content_map[".zip"] = "application/zip";
    content_map[".3gp"] = "video/3gpp audio/3gpp";
    content_map[".3g2"] = "video/3gpp2 audio/3gpp2";
    content_map[".7z"] = "application/x-7z-compressed";
    content_map[".txt"] = "text/plain";

    return (content_map);
}
