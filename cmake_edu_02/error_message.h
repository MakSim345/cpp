#pragma once
#include "gen.h"

class error_message
{
public:
	error_message();
	void printMessage() const;

private:
	const char* message;
};

