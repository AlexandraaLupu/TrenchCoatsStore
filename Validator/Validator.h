#pragma once
#include "../Domain/Domain.h"
#include <string>
class ValidationException {
private:
	std::string message;
public:
	ValidationException(std::string _message);
	std::string getMessage() const;
	
};

class TrenchCoatValidator {
public:
	TrenchCoatValidator() = default;
	void validate(const TrenchCoat& t);
	~TrenchCoatValidator() = default;
};