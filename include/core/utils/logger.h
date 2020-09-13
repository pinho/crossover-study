#ifndef _CORE_UTILS_LOGGER_H
#define _CORE_UTILS_LOGGER_H 1

#include <string>
#include <iostream>
using std::endl;

class Log {
public:
  enum mod {
    breakline,
    no_breakline
  };

  // void set_stream(std::ostream &os);

  static void message(const char* msg, mod m = mod::breakline) {
    s_stream << msg;
    if (m == mod::breakline) {
      s_stream << std::endl;
    }
  }

  static void message(std::string msg, mod m = mod::breakline) {
    s_stream << msg;
    if (m == mod::breakline) {
      s_stream << std::endl;
    }
  }

private:
  static std::ostream& s_stream;
};

#define SET_LOG_STREAM(stream_name) Log::s_stream = std::cout;

#endif 