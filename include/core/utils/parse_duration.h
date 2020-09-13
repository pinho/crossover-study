#ifndef TIME_PARSE_HPP_
#define TIME_PARSE_HPP_

#include <chrono>
#include <sstream>
#include <string>
using std::chrono::nanoseconds;

/**
 * Analisar um valor de procurando formatar em segundos, minutos ou horas,
 * dependendo do tamanho */
std::string parse_duration(nanoseconds& dur);

#endif