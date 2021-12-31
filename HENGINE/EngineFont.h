#pragma once
#include "Resources.h"

#ifdef X32
#ifdef DEBUGMODE

#pragma comment(lib, "FW1FontWrapperD32.lib")
#elif RELEASEMODE
#pragma comment(lib, "FW1FontWrapperR32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "FW1FontWrapperD64.lib")
#elif RELEASEMODE
#pragma comment(lib, "FW1FontWrapperR64.lib")
#endif
#endif

#include <FW1CompileSettings.h>
#include <FW1FontWrapper.h>

class EngineFont : public Resources
{
private:
	IFW1Factory* m_pFontFactory;
	IFW1FontWrapper* m_pFontWrapper;

public:
	bool Create(const wchar_t* _FontName);
	void DrawWorld(const wchar_t* _Text, float _fSize, Vector4 Pos, Vector4 COLOR, FW1_TEXT_FLAG _Flag);

	// ��ũ����ǥ�� �������� �ϹǷ� ĳ���� �Ӹ����� ĳ���� ���� ���� �ʹٴ��� �ϸ�
	// ���� ��ǥ�迡�� ��ũ�� ��ǥ��� ��ȯ�ؼ� ��ġ�� �־��ָ� �ɰ��̴�.
	void DrawUI(const wchar_t* _Text, float _fSize, Vector4 Pos, Vector4 COLOR, FW1_TEXT_FLAG _Flag = FW1_TOP);

public:
	EngineFont();
	~EngineFont();
};

