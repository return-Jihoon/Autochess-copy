#include "EffectRotate.h"

#include <JTime.h>

void EffectRotate::Init()
{

}

void EffectRotate::Update()
{

	curTime += Time::DeltaTime();
	
	if (dir == 1)  //yȸ��
	{
		GetActor()->GetTransform()->SetLocalRotY(rotSpeed * curTime);
	}
	else if (dir == 2) //xȸ��
	{
		GetActor()->GetTransform()->SetLocalRotX(rotSpeed * curTime);
	}
	else if (dir == 3) //z ȸ��
	{
		GetActor()->GetTransform()->SetLocalRotZ(rotSpeed * curTime);
	}
	

}


EffectRotate::EffectRotate() : curTime(0.0f), dir(1), rotSpeed(500.0f)
{
	
}


EffectRotate::~EffectRotate()
{

}
