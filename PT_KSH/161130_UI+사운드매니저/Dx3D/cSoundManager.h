#pragma once

#define g_pSoundManager cSoundManager::GetInstance()

class cSoundManager
{
private:
	SINGLETONE(cSoundManager);

private:

public:
	//

	//
	void Destroy();
};
