#pragma once
#ifndef __RENDERING_SYSTEM_H__
#define __RENDERING_SYSTEM_H__
#include <windows.h>
#include <tchar.h>


namespace System {
	// This system creates the window
	class RenderingSystem {
	private: 
		HINSTANCE hInstance; 
		HINSTANCE previousInstance; 
		PSTR cmdLine; 
		INT nCmdShow;
		TCHAR* szTitle;
	public:
		RenderingSystem(HINSTANCE _hInstance, HINSTANCE _previousInstance, PSTR _cmdLine, INT _nCmdShow);
		~RenderingSystem();
		void CreateWindow();

	};
}
#endif // __INPUT_SYSTEM_H__
