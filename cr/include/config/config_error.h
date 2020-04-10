//
// Created by ronaldd on 09/04/2020.
//

#ifndef CROSSOVERRESEARCH_CONFIG_ERROR_H
#define CROSSOVERRESEARCH_CONFIG_ERROR_H

#include <stdexcept>
#include <exception>

class ConfigError : public std::logic_error {
public:
	ConfigError(std::string errormsg) : std::logic_error(errormsg) {}
};

class LabelNotDefinedError : ConfigError {
public:
	LabelNotDefinedError(std::string label)
	: ConfigError("Label \""+label+"\" was not defined") {}
};

class NullLabelError : ConfigError {
public:
	NullLabelError(std::string label)
	: ConfigError("Label \""+label+"\" is null") {}
};

class NotScalarError : ConfigError {
public:
	NotScalarError(std::string label)
	: ConfigError("Label \""+label+"\" is not a scalar") {}
};

#endif //CROSSOVERRESEARCH_CONFIG_ERROR_H
