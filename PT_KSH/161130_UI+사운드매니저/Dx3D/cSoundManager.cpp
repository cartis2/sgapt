#include "stdAfx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
	:m_soundType(SOUNDNULL)
{
}

cSoundManager::~cSoundManager()
{
}
HRESULT cSoundManager::SoundInit2D(void)
{
	//사운드 시스템 생성
	System_Create(&m_2Dsystem);

	//maxchannels : fomd 에서 사용하는 최대 채널의 수를 뜻함
	//사운드 채널수 생성
	m_2Dsystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);



	//3d 사운드 세팅 필요
	//m_2Dsystem->set3DSettings()
	//



	//사운드 , 채널 동적할당
	m_2Dsound = new FMOD::Sound *[TOTALSOUNDBUFFER];
	m_2Dchannel = new FMOD::Channel *[TOTALSOUNDBUFFER];

	//메모리 초기화
	memset(m_2Dsound, 0, sizeof(FMOD::Sound*)* (TOTALSOUNDBUFFER));
	memset(m_2Dchannel, 0, sizeof(FMOD::Channel*)* (TOTALSOUNDBUFFER));

	return S_OK;
}
void cSoundManager::SoundRelease2D(void)
{
	//사운드 및 채널 삭제
	if (m_2Dchannel != NULL || m_2Dsound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (m_2Dchannel != NULL)
			{
				if (m_2Dchannel[i]) m_2Dchannel[i]->stop();
			}

			if (m_2Dsound != NULL)
			{
				if (m_2Dsound[i]) m_2Dsound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE(m_2Dchannel);
	SAFE_DELETE(m_2Dsound);

	//시스템 닫기
	if (m_2Dsystem != NULL)
	{
		m_2Dsystem->release();
		m_2Dsystem->close();
	}
}
void cSoundManager::SoundUpdate2D(void)
{
	/*
	사운드 시스템을 계속 업데이트 해줘야 볼륨이 바뀌거나
	재성이 끝난 사운드를 채널에서 빼내는 등 다양한 작업을 자동으로 해준다
	*/
	//메인게임에서 사운드매니져를 업데이트 해준다
	m_2Dsystem->update();
}
//void cSoundManager::render(void)
//{
//}

//사운드 추가(키값, 파일이름, BGM?, 루프냐?, 2D냐 3D냐?)
void cSoundManager::addSound2D(std::string keyName, std::string soundName, bool bgm, bool loop, bool type)
{
	//type 매개변수는 사운드의 종류가 2D(false), 3D(true)
	if (type)
	{
		//3D sound
		//3d 사운드 추가
		//m_2Dsystem->set3DSettings(1.0, 1.0, 1.0);
		//m_2Dsystem->createSound(soundName.c_str(), FMOD_3D, 0, &m_2Dsound[m_2DTotalSounds.size()]);
		//m_2Dsound[m_2DTotalSounds.size()]->set3DMinMaxDistance(0.5f, 5000.0f);
		//m_2Dsound[m_2DTotalSounds.size()]->setMode(FMOD_LOOP_NORMAL);
		//
	}
	else
	{
		//2D Sound
		if (loop)//브금 or 이펙트
		{
			if (bgm)
			{
				//1: 파일 URL의 이름 
				//2: 사운드를 열기 위한 옵션	
				//3: 사운드를 재생하는 동안 유저에게 정보를 제공하는 FMOD_CREATESOUNDEXINFO의 포인터 , 이옵션을 무시하려면 0 또는 NULL을 지정하면 됨
				//4: FMOD::SOUND 오브젝트를 받는 변수의 주소
				m_2Dsystem->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_2Dsound[m_2DTotalSounds.size()]);
			}
			else
			{
				m_2Dsystem->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_2Dsound[m_2DTotalSounds.size()]);
			}
		}
		else  //이펙트
		{
			m_2Dsystem->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &m_2Dsound[m_2DTotalSounds.size()]);
		}		

		//맵에 사운드를 키값과 함께 담아준다
		m_2DTotalSounds.insert(make_pair(keyName, &m_2Dsound[m_2DTotalSounds.size()]));
	}
	
}

//사운드 플레이(키값, 볼륨) 0.0f~ 1.0f
void cSoundManager::play2D(std::string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			m_2Dsystem->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_2Dchannel[count]);
			

			////3d 사운드 세팅
			//FMOD_VECTOR pos = { -10.0f * 0.1f, 0.0f, 0.0f };
			//FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

			//m_2Dchannel[count]->set3DAttributes(&pos, &vel);

			////


			//볼륨셋팅
			m_2Dchannel[count]->setVolume(volume);
			break;
		}
	}
}
//사운드 정지
void cSoundManager::stop2D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			m_2Dchannel[count]->stop();
			break;
		}
	}
}
//사운드 일시정지
void cSoundManager::pause2D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			m_2Dchannel[count]->setPaused(true);
			break;
		}
	}
}
//사운드 다시 재생
void cSoundManager::resume2D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시정지(다시재생)
			m_2Dchannel[count]->setPaused(false);
			break;
		}
	}
}

//플레이 중이냐?
bool cSoundManager::isPlaySound2D(std::string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//플레이 중이냐?
			m_2Dchannel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}
//일시정지 중이냐?
bool cSoundManager::isPauseSound2D(std::string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = m_2DTotalSounds.begin();
	for (iter; iter != m_2DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//플레이 중이냐? (일시정지)
			m_2Dchannel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}



HRESULT cSoundManager::SoundInit3D(void)
{
	System_Create(&m_3Dsystem);

	m_3Dsystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//3d 사운드 세팅 필요
	//m_3Dsystem->set3DSettings()
	//

	//사운드 , 채널 동적할당
	m_3Dsound = new FMOD::Sound *[TOTALSOUNDBUFFER];
	m_3Dchannel = new FMOD::Channel *[TOTALSOUNDBUFFER];

	//메모리 초기화
	memset(m_3Dsound, 0, sizeof(FMOD::Sound*)* (TOTALSOUNDBUFFER));
	memset(m_3Dchannel, 0, sizeof(FMOD::Channel*)* (TOTALSOUNDBUFFER));

	return S_OK;
}
void cSoundManager::SoundRelease3D(void)
{
	//사운드 및 채널 삭제
	if (m_3Dchannel != NULL || m_3Dsound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (m_3Dchannel != NULL)
			{
				if (m_3Dchannel[i]) m_3Dchannel[i]->stop();
			}

			if (m_3Dsound != NULL)
			{
				if (m_3Dsound[i]) m_3Dsound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE(m_3Dchannel);
	SAFE_DELETE(m_3Dsound);

	//시스템 닫기
	if (m_3Dsystem != NULL)
	{
		m_3Dsystem->release();
		m_3Dsystem->close();
	}
}
void cSoundManager::SoundUpdate3D(void)
{
	m_3Dsystem->update();
}

//사운드 추가(키값, 파일이름, BGM?, 루프냐?, 2D냐 3D냐?)
void cSoundManager::addSound3D(std::string keyName, std::string soundName, bool bgm, bool loop, bool type, FMOD_VECTOR pos, FMOD_VECTOR vel)
{
	//type 매개변수는 사운드의 종류가 2D(false), 3D(true)
	if (type)
	{
		//3D sound
		//3d 사운드 추가
		//m_2Dsystem->set3DSettings(1.0, 1.0, 1.0);
		//m_2Dsystem->createSound(soundName.c_str(), FMOD_3D, 0, &m_2Dsound[m_2DTotalSounds.size()]);
		//m_2Dsound[m_2DTotalSounds.size()]->set3DMinMaxDistance(0.5f, 5000.0f);
		//m_2Dsound[m_2DTotalSounds.size()]->setMode(FMOD_LOOP_NORMAL);
		//
	}
	else
	{
		//2D Sound
		if (loop)//브금 or 이펙트
		{
			if (bgm)
			{
				//1: 파일 URL의 이름 
				//2: 사운드를 열기 위한 옵션	
				//3: 사운드를 재생하는 동안 유저에게 정보를 제공하는 FMOD_CREATESOUNDEXINFO의 포인터 , 이옵션을 무시하려면 0 또는 NULL을 지정하면 됨
				//4: FMOD::SOUND 오브젝트를 받는 변수의 주소
				//3Dsystem->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_3Dsound[m_3DTotalSounds.size()]);
			}
			else
			{
				m_3Dsystem->createSound(soundName.c_str(), FMOD_3D, 0, &m_3Dsound[m_3DTotalSounds.size()]);
				m_3Dsound[m_3DTotalSounds.size()]->set3DMinMaxDistance(0.5f, 5000.0f);
				m_3Dsound[m_3DTotalSounds.size()]->setMode(FMOD_DEFAULT);
				
				//m_3Dsystem->set3DListenerAttributes(
				//	0,		// listener ID, 0일 경우 listener가 하나
				//	&pos,	// 월드 스페이스에서의 listener position
				//	&vel,	// 초당 listener의 속도
				//	&dir,	// listener의 방향 벡터
				//	&up		// listener의 노멀 벡터
				//);	
					
			}
		}
		else  //이펙트
		{
			m_3Dsystem->createSound(soundName.c_str(), FMOD_3D, 0, &m_3Dsound[m_3DTotalSounds.size()]);
			m_3Dsound[m_3DTotalSounds.size()]->set3DMinMaxDistance(0.5f, 5000.0f);
			m_3Dsound[m_3DTotalSounds.size()]->setMode(FMOD_DEFAULT);
			//m_3Dsystem->set3DListenerAttributes(0, &pos, &vel, &dir, &up);
		}
		//3d 사운드 listener 설정
		FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR dir = { 0.0f, 1.0f, 0.0f };
		FMOD_VECTOR up = { 0.0f, 0.0f, 1.0f };

		m_3Dsystem->set3DListenerAttributes(
				0,		// listener ID, 0일 경우 listener가 하나
				&pos,	// 월드 스페이스에서의 listener position
				&vel,	// 초당 listener의 속도
				&dir,	// listener의 방향 벡터
				&up		// listener의 노멀 벡터
			);	

		//3d 사운드 세팅
		FMOD_VECTOR vPos = pos;
		FMOD_VECTOR vVel = vel;
		
		//m_3Dpos.insert(keyName, vPos);
		m_3Dpos.push_back(vPos);
		m_3Dpos.push_back(vVel);
		//맵에 사운드를 키값과 함께 담아준다
		m_3DTotalSounds.insert(make_pair(keyName, &m_3Dsound[m_3DTotalSounds.size()]));
	}

}
//사운드 플레이(키값, 볼륨) 0.0f~ 1.0f
void cSoundManager::play3D(std::string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			m_3Dsystem->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_3Dchannel[count]);


			//3d 사운드 세팅
			FMOD_VECTOR pos = m_3Dpos[count];
			FMOD_VECTOR vel = m_3Dvel[count];
			
			m_3Dchannel[count]->set3DAttributes(&pos, &vel);

			//
			//볼륨셋팅
			m_3Dchannel[count]->setVolume(volume);
			break;
		}
	}
}
//사운드 정지
void cSoundManager::stop3D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			m_3Dchannel[count]->stop();
			break;
		}
	}
}
//사운드 일시정지
void cSoundManager::pause3D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			m_3Dchannel[count]->setPaused(true);
			break;
		}
	}
}
//사운드 다시 재생
void cSoundManager::resume3D(std::string keyName)
{
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시정지(다시재생)
			m_3Dchannel[count]->setPaused(false);
			break;
		}
	}
}

//플레이 중이냐?
bool cSoundManager::isPlaySound3D(std::string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//플레이 중이냐?
			m_3Dchannel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}
//일시정지 중이냐?
bool cSoundManager::isPauseSound3D(std::string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = m_3DTotalSounds.begin();
	for (iter; iter != m_3DTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//플레이 중이냐? (일시정지)
			m_3Dchannel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}

void cSoundManager::Destroy()
{
	for each(auto it in m_2DTotalSounds)
	{
		SAFE_DELETE(it.second);
	}

	for each(auto it in m_3DTotalSounds)
	{
		SAFE_DELETE(it.second);
	}
}