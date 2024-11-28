#ifndef __ABSTRACT_CLASS_ERROR_H__
#define __ABSTRACT_CLASS_ERROR_H__

#include <stdexcept>

class AbstractClassError : std::exception {
	std::string message;

    public:
	AbstractClassError()
		: message("This class isn't supposed to be constructed.")
	{
	}
	const char *what() const noexcept override
	{
		return message.c_str();
	}
};
#endif