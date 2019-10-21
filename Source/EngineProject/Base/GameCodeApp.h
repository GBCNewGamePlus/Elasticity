#pragma once

#ifndef __GAME_CODE_APP_H__
#define __GAME_CODE_APP_H__
#include <windows.h>
class GameCodeApp 
{
private:
	bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	void ReadCPUSpeed();
protected:
public:
	bool InitInstance();
	bool IsOnlyInstance(LPCTSTR windowName);
};

#endif // __GAME_CODE_APP_H__
