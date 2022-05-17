#include "DataStruct.h"

using namespace ds;

_Path::_Path(std::string string):string(string)
{
}

_Name::_Name(std::string string):string(string)
{
}

_Path _Path::operator+ (const _Path& other){

	return _Path(this->string + other.string);
}