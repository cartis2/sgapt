#pragma once

#include "inc/fmod.h"
#include "inc/fmod.hpp"		//fomd.hpp 추가
#pragma comment(lib, "lib/fmodex_vc.lib")	//lib 링크
//using namespace FMOD;			//FMOD 네임스페이스 사용

//채널버퍼, 사운드버퍼
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 20
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER	//총사운드 버퍼설정: 버퍼가 작아서 씹히는 문제를 해결해주기 위함

#define g_pSoundManager cSoundManager::GetInstance()

enum SOUNDTYPE
{
	SOUNDNULL = 0,
	BGM,		//배경음악
	SPEECH,		//대사
	EFFECT,		//효과음
	AMBIENT		//환경음
};

class cSoundManager
{
private:
	typedef std::map<std::string, FMOD::Sound**> arrSounds;
	typedef std::map<std::string, FMOD::Sound**>::iterator arrSoundIter;

	
private:
	SOUNDTYPE		m_soundType;

	//2D Sound
	FMOD::System*	m_2Dsystem;			//fmod의 시스템 클래스
	FMOD::Sound**	m_2Dsound;			//fmod의 사운드 클래스
	FMOD::Channel** m_2Dchannel;		//fmod의 채널 클래스

	arrSounds		m_2DTotalSounds;	//맵에 담긴 사운드 목록
	
	//3D Sound
	FMOD::System*	m_3Dsystem;			//fmod의 시스템 클래스
	FMOD::Sound**	m_3Dsound;			//fmod의 사운드 클래스
	FMOD::Channel** m_3Dchannel;		//fmod의 채널 클래스

	arrSounds		m_3DTotalSounds;	//맵에 담긴 사운드 목록

	//FMOD_VECTOR		m_3Dpos;			//사운드의 위치
	//FMOD_VECTOR		m_3Dvel;			//사운드의 위치
	//typedef std::map<std::string, FMOD_VECTOR> arr3DSoundPos;
	//typedef std::map<std::string, FMOD_VECTOR> arr3DSoundVel;
	//arr3DSoundPos	m_3Dpos;
	//arr3DSoundVel	m_3Dvel;

	std::vector<FMOD_VECTOR>	m_3Dpos;	
	std::vector<FMOD_VECTOR>	m_3Dvel;

private:
	SINGLETONE(cSoundManager);

public:
	//2D Sound
	HRESULT SoundInit2D(void);
	void SoundRelease2D(void);
	void SoundUpdate2D(void);
	//void render(void);

	//3D Sound
	HRESULT SoundInit3D(void);
	void SoundRelease3D(void);
	void SoundUpdate3D(void);

	//사운드 추가(키값, 파일이름, BGM?, 루프냐?)
	void addSound2D(std::string keyName, std::string soundName, bool bgm = FALSE, bool loop = FALSE, bool type = FALSE);
	//사운드 플레이(키값, 볼륨) 0.0f~ 1.0f
	void play2D(std::string keyName, float volume = 1.0f);
	//사운드 정지
	void stop2D(std::string keyName);
	//사운드 일시정지
	void pause2D(std::string keyName);
	//사운드 다시 재생
	void resume2D(std::string keyName);

	//플레이 중이냐?
	bool isPlaySound2D(std::string keyName);
	//일시정지 중이냐?
	bool isPauseSound2D(std::string keyName);
	//



	//사운드 추가(키값, 파일이름, BGM?, 루프냐?)
	void addSound3D(std::string keyName, std::string soundName, bool bgm = FALSE, bool loop = FALSE, bool type = FALSE, FMOD_VECTOR pos = { 0,0,0 }, FMOD_VECTOR vel = { 0,0,0 });
	//사운드 플레이(키값, 볼륨) 0.0f~ 1.0f
	void play3D(std::string keyName, float volume = 1.0f);
	//사운드 정지
	void stop3D(std::string keyName);
	//사운드 일시정지
	void pause3D(std::string keyName);
	//사운드 다시 재생
	void resume3D(std::string keyName);
	                                                                 
	//플레이 중이냐?
	bool isPlaySound3D(std::string keyName);
	//일시정지 중이냐?
	bool isPauseSound3D(std::string keyName);
	//
	void Destroy();
	
};
