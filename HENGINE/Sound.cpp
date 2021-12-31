#include "Sound.h"
#include "Debug.h"
#include <string>
#include "Path.h"
#include "JTemplate.h"
#include <list>

// wchar -> char�� ���� ���
#include <atlstr.h>

FMOD_RESULT __stdcall Sound::SoundPlayerCallBack(
	FMOD_CHANNELCONTROL *channelcontrol,
	FMOD_CHANNELCONTROL_TYPE controltype,
	FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
	void *commanddata1,
	void *commanddata2)
{
	switch (controltype)
	{
	case FMOD_CHANNELCONTROL_CHANNEL:

		switch (callbacktype)
		{
		case FMOD_CHANNELCONTROL_CALLBACK_END:
		{
			FMOD::Channel* pPointer = ((FMOD::Channel*)channelcontrol);
			void* pSoundPlayer = nullptr;
			pPointer->getUserData(&pSoundPlayer);
			if (nullptr == pSoundPlayer)
			{
				BOOM;
			}

			//HSoundPlayer* CallPlayer = (HSoundPlayer*)pSoundPlayer;

			//if (true == CallPlayer->IsRental())
			//{
			//	return FMOD_OK;
			//}

			//CallPlayer->ReturnPool();

			return FMOD_OK;
		}
		case FMOD_CHANNELCONTROL_CALLBACK_VIRTUALVOICE:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_SYNCPOINT:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_OCCLUSION:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_MAX:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_FORCEINT:
			break;
		default:
			break;
		}
		break;
	case FMOD_CHANNELCONTROL_CHANNELGROUP:
		break;
	case FMOD_CHANNELCONTROL_MAX:
		break;
	case FMOD_CHANNELCONTROL_FORCEINT:
		break;
	default:
		break;
	}

	return FMOD_OK;
}

void SoundPlayer::Stop() 
{
	if (nullptr == m_pChannel)
	{
		BOOM;
	}

	m_pChannel->stop();
	m_pChannel = nullptr;
}


FMOD::System* Sound::m_pMainSoundSystem = nullptr;
std::map<std::wstring, HPTR<SoundPlayer>> Sound::m_PlayList;

bool Sound::Init() 
{
	FMOD_RESULT Return = FMOD::System_Create(&m_pMainSoundSystem);
	if (nullptr == m_pMainSoundSystem || FMOD_OK != Return)
	{
		BOOM;
		return false;
	}

	// ���ÿ� ��� ���尡 Ʋ������ �ִ��Ŀ� ���Ѱ�.
	// 32ä���̸� 8012�� �ΰ�????
	Return = m_pMainSoundSystem->init(32, FMOD_DEFAULT, nullptr);
	if (FMOD_OK != Return)
	{
		BOOM;
		return false;
	}

	return true;
}

// ����Ƽ������ 3D�ɼ� �̷��͵��� ����.
// �������.
void Sound::Play(const wchar_t* _Name) 
{
	HPTR<Sound> FindSound = Resources::Find<Sound>(_Name);

	if (nullptr == FindSound)
	{
		BOOM;
		return;
	}


	Sound::m_pMainSoundSystem->playSound(FindSound->m_pSound, nullptr, false, nullptr);
}

HPTR<SoundPlayer> Sound::FindPlayer(const wchar_t* _PlayerName) 
{
	std::map<std::wstring, HPTR<SoundPlayer>>::iterator FindPlayerIter = m_PlayList.find(_PlayerName);

	if (FindPlayerIter == m_PlayList.end())
	{
		return nullptr;
	}

	return FindPlayerIter->second;
}

void Sound::Play(const wchar_t* _PlayerName, const wchar_t* _Name, int _LoopCount /*= 1*/)
{
	HPTR<Sound> FindSound = Resources::Find<Sound>(_Name);

	if (nullptr == FindSound)
	{
		BOOM;
		return;
	}


	if (nullptr != FindPlayer(_PlayerName))
	{
		SoundPlayer* NewPlayer = FindPlayer(_PlayerName);
		Sound::m_pMainSoundSystem->playSound(FindSound->m_pSound, nullptr, false, &NewPlayer->m_pChannel);
	}
	else
	{
		SoundPlayer* NewPlayer = new SoundPlayer();
		Sound::m_pMainSoundSystem->playSound(FindSound->m_pSound, nullptr, false, &NewPlayer->m_pChannel);

		if (nullptr == NewPlayer->m_pChannel)
		{
			BOOM;
		}

		NewPlayer->m_pChannel->setCallback(SoundPlayerCallBack);
		NewPlayer->m_pChannel->setUserData(NewPlayer);
		NewPlayer->m_pChannel->setMode(FMOD_LOOP_NORMAL /*| FMOD_2D*/);
		NewPlayer->m_pChannel->setLoopCount(_LoopCount);

		m_PlayList.insert(std::map<std::wstring, HPTR<SoundPlayer>>::value_type(_PlayerName, NewPlayer));
	}

	
}

void Sound::Stop(const wchar_t* _PlayerName)
{
	HPTR<SoundPlayer> FindPlaySound = FindPlayer(_PlayerName);

	if (nullptr == FindPlaySound)
	{
		BOOM;
		return;
	}

	FindPlaySound->Stop();
}

void Sound::Update()
{
	if (nullptr != m_pMainSoundSystem)
	{
		m_pMainSoundSystem->update();
	}
}


Sound::Sound()
{
}


Sound::~Sound()
{
	if (nullptr != m_pSound)
	{
		m_pSound->release();
	}
}


bool Sound::Load() 
{
	// MultiByteToWideChar
	// WideCharToMultiByte
	// wchar to ascii 
	// CP_UTF8�ѱ۵��� ����Ҷ� ���ʿ�
	// ���ڿ��� ǥ���ϴ� ����̳� �������� ������ ����.
	// �ѱ��� 3����Ʈ�� ǥ���ϴ� ���� ���.
	// ������������ �������� �ִµ� ����
	// �ٴ� ���α׷��ֿ��� ���� ���� ����ϴ� ����� UTF��� �����ϸ� �ȴ�.
	// 8 16 32
	// ��θ� �ѱ۷� �Ǿ��ִ� �е��� �̰� �����ָ� �����̴ϴ�.
	std::string Str = CW2A(m_File.GetFullPath(), CP_UTF8).m_psz;

	FMOD_RESULT Return = m_pMainSoundSystem->createSound(Str.c_str(), FMOD_DEFAULT, nullptr, &m_pSound);

	if (FMOD_OK != Return || nullptr == m_pSound)
	{
		BOOM;
	}
	return true;
}

