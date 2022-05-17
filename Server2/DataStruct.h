#pragma once
#include "Log.h"
#include <fstream>
#include <iostream>
#include <string>


namespace ds {
	class _Path {
	public:
		std::string string;
		_Path(std::string string);
		_Path operator+ (const _Path& other);
	};
	class _Name {
	public:
		std::string string;
		_Name(std::string string);
	};
	enum LoadType {
		LoadFromFile,
		CreateDataStruct
	};
	class DataStruct
	{
	public:
		virtual void Save(const _Path& path) = 0;
		virtual void Load(const _Path& path) = 0;
		virtual const _Path& GetFullPath(const _Name& name) = 0;
		virtual void Destroy() = 0;
	};
}


