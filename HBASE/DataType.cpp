#include "DataType.h"
#include <iostream>


DataType::DataType() : mInfo(nullptr)
{
}


DataType::~DataType()
{
}

// 기초.. 
void DataType::TypeSetting()
{
	
	// 문법적으로 봤을때 
	mInfo = &typeid(*this);




	std::cout << mInfo->name() << std::endl;
}