#include <iostream>
#include "windows.h"
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <ctype.h>
#include <basetsd.h> 
#include <winnt.h>
#include <tchar.h>
#include "GameEngine.h"

# define GCC_NEW new(NORMAL_BLOCK,FILE, __LINE_)
using namespace std;


// Use this main to test multiple instance detection.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, PSTR cmdLine, INT nCmdShow)
{
	GameEngine engine( hInstance,  previousInstance,  cmdLine,  nCmdShow);
	return 0;
}

// Use this main to see the output on the console.
