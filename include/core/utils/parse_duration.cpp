#include "parse_duration.h"

std::string parse_duration(std::chrono::nanoseconds& dur) {
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
