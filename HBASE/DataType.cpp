#include "DataType.h"
#include <iostream>


DataType::DataType() : mInfo(nullptr)
{
}


DataType::~DataType()
{
}

// ����.. 
void DataType::TypeSetting()
{
	
	// ���������� ������ 
	mInfo = &typeid(*this);




	std::cout << mInfo->name() << std::endl;
}