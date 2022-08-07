#include "DxLib.h"
#include "SystemMain.h"

// ƒvƒƒOƒ‰ƒ€‚Í WinMain ‚©‚çn‚Ü‚è‚Ü‚·
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SystemMain Systemmain;

	if (Systemmain.initialize())
	{
		Systemmain.main();
	}

	Systemmain.finalize();


	return 0;
}