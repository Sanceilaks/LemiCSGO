#include "LockCursorHook.h"
#include "HackCore.h"
#include "menu.h"

namespace MyHooks
{
	bool __stdcall MyLockCursor()
	{
		if (HackCore::GetInstance()->MyGlobals->MenuIsOpen)
		{
			HackCore::GetInstance()->Surface->UnlockCursor();
			HackCore::GetInstance()->InputSystem->reset_input_state();
			return true;
		}
		return false;
	}
}