#ifndef TIME_PARSE_HPP_
#define TIME_PARSE_HPP_

#include <chrono>
#include <sstream>

/**
 * Analisar um valor de procurando formatar em segundos, minutos ou horas,
 * dependendo do tamanho */
std::string parse_duration(std::chrono::nanoseconds dur) {
  using namespace std::chrono;
  std::stringstream ss;

  auto h = duration_cast<hours>(dur);
  dur -= h;
  auto m = duration_cast<minutes>(dur);
  dur -= m;
  auto s = duration_cast<seconds>(dur);
  dur -= s;
  auto ms = duration_cast<milliseconds>(dur);
  
  ss << h.count() << "h " << m.count() << "m "
     << s.count() << "s " << ms.count() << "ms";

  return ss.str();
}

#endif