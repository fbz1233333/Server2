#pragma once
class Exception
{
public:
	enum ExceptionType {
		INII_DLL,
	} ;
	static void Throw(ExceptionType type);
};

