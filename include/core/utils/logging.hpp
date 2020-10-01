#ifndef LOGGING_HPP_
#define LOGGING_HPP_ 1

#include <cstdio>

#ifdef __unix__
# define __UNIX_HIGHLIGHT_BG_LABEL__(color, text) "\e[1;3;"#color"m "text" \e[0m "
# define __UNIX_ERROR_LABEL__ "\e[1;3;101m Error \e[0m "
# define __UNIX_WARNING_LABEL__ "\e[1;3;30;43m Warn \e[0m "
#endif

#undef stdlog
#define stdlog std::cout
#undef stderrlog
#define stderrlog std::cerr

#define __default_print(format, ...) printf(format __VA_OPT__(,) __VA_ARGS__)
#define log(format, ...) __default_print(format __VA_OPT__(,) __VA_ARGS__)

#ifdef __unix__
# define warn(format, ...) printf(__UNIX_WARNING_LABEL__); log(format __VA_OPT__(,) __VA_ARGS__)
# define err(format, ...) printf(__UNIX_ERROR_LABEL__); log(format __VA_OPT__(,) __VA_ARGS__)
#else
# define warn(format, ...) printf("Warning: "); log(format __VA_OPT__(,) __VA_ARGS__)
# define err(format, ...) printf("Error: "); log(format __VA_OPT__(,) __VA_ARGS__)
#endif

#endif