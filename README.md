# Crossovers Comparison

![Actions Status](https://github.com/pinho/crossover-research/workflows/C++%20CI/badge.svg)

Comparison of Crossover operators in Genetic Algorithms for some combinatorial
optimization problems.

## How to Build

1 . Make sure that CMAKE is installed in 3.15+ version or install it.

2 . Create a folder for hold the build files:

```shell script
mkdir build
cd build
```

3 . Use cmake to generate Makefiles:

```shell script
cmake .. [-DBUILD_TESTING=ON|OFF][-DINSTALL_HEADERS=ON|OFF]
``` 

For compile unit test suites use the option `-DBUILD_TESTING=ON`.

For install the headers on `make install` command use option `-DINSTALL_HEADERS=ON`.

4 . Install all targets using:
```shell script
$ make install # can be requires sudo
```

## License

This work is licensed under
[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)
&copy; Ronaldd Pinho
