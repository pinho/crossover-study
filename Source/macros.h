#ifndef MACROS_H_
#define MACROS_H_

#ifdef __unix__
#  define PRINT(text) std::cout << text << std::flush;
#  define PRINTLN(text) std::cout << text << std::endl;

#  define PRINT_GREEN(text) std::cout << "\e[38;5;47m" << text << "\e[0m" << std::flush;

#  define PRINT_GREEN_BG(text) std::cout << "\e[48;5;46m " << text << " \e[0m" << std::flush;

#  define PRINT_RED(text) std::cout << "\e[38;5;196m" << text << "\e[0m" << std::flush;

#  define PRINT_RED_BG(text) std::cout << "\e[48;5;197m " << text << " \e[0m" << std::flush;
#endif

#endif