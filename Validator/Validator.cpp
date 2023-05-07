#include "Validator.h"

ValidationException::ValidationException(std::string _message): message{_message}
{
}

std::string ValidationException::getMessage() const
{
	return this->message;
}

void TrenchCoatValidator::validate(const TrenchCoat& t)
{
	string errors;
	string size = t.getSize();
	if (size != "S" && size != "M" && size != "L")
		errors += string("Size must be S, M or L.\n");
	if (t.getColor().size() < 3)
		errors += string("Color must have more than 2 characters.\n");
	if (t.getQuantity() < 0)
		errors += string("Quantity must be a positive number.\n");
	if (t.getPrice() < 0)
		errors += string("Price must be a positive number.\n");
	if (t.getPhotograph().size() <= 3)
		errors += string("The photograph link must have more than 7 characters.\n");
	//if (t.getPhotograph().find("www.") == string::npos  t.getPhotograph().find("default") == string::npos)
		//errors += string("Link must have \"www.\".\n");
	if (errors.size() > 0)
		throw ValidationException(errors);
}
