#pragma once
#include "Resources.h"

#include <fmod.hpp>
#include <map>
#include <set>
// FILO ó�� �߰��ѳ༮�� �������� ���´�.
// ������ ����� ����Ʈ���� ����� ������ �༮.
#include <stack>



#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "fmodL_vc.lib")
#elif RELEASEMODE
#pragma comment(lib, "fmod_vc.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "fmodL_vc.lib")
#elif RELEASEMODE
#pragma comment(lib, "fmod_vc.lib")
#endif
#endif

class Sound;
class SoundPlayer : public Reference
{
	friend Sound;

private:
	Sound* m_SoundClip;
	FMOD::Channel* m_pChannel;

public:
	void Stop();
};

class Sound : public Resources
{
public:
	static FMOD::System* m_pMainSoundSystem;

	static FMOD_RESULT __stdcall SoundPlayerCallBack(
		FMOD_CHANNELCONTROL *channelcontrol,
		FMOD_CHANNELCONTROL_TYPE controltype,
		FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
		void *commanddata1,
		void *commanddata2);


	static bool Init();
	static void Update();

	// Stop�� ����Ų��.
	static void Play(const wchar_t* _Name);

	// ����� 
	static void Play(const wchar_t* _PlayerName, const wchar_t* _Name, int _LoopCount = 1);
	static void Stop(const wchar_t* _PlayerName);

	static HPTR<SoundPlayer> FindPlayer(const wchar_t* _PlayerName);

	static std::map<std::wstring, HPTR<SoundPlayer>> m_PlayList;


	// FMOD::Channel* m_pChannel;

private:
	FMOD::Sound* m_pSound;

	// �и������� ������ �����Ѵ�.
public:
	unsigned int SoundLen()
	{
		unsigned int Value = -1;
		m_pSound->getLength(&Value, FMOD_TIMEUNIT_MS);
		return Value;
	}

public:
	bool Load();


public:
	Sound();
	~Sound();
};

