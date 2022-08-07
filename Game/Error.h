#pragma once



class Error
{
public:
	static void finish(char* errorMessage, LPCTSTR lpszFuncName, int lineN);
};

