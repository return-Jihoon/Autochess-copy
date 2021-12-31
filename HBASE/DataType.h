#pragma once
#include <typeinfo>

class DataType
{
public:
	void TypeSetting();
	bool IsType(const type_info* _Info)
	{
		return mInfo == _Info;
	}
	template<typename T>
	bool IsType() 
	{
		return mInfo == &typeid(T);
	}
	bool IsType(const DataType& _Name)
	{
		return mInfo == _Name.mInfo;
	}

private:
	const type_info* mInfo;

public:
	DataType();
	virtual ~DataType();
};

