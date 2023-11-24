#include "stdafx.h"

#include <Windows.h>
#include <iostream>

using namespace std;

#define EN_US 0x0409
#define ZH_CN 0x0804

/*
*  Check if current keyboard layout is English.
*/
bool IsEnglish() {
    HKL hkl = GetKeyboardLayout(
        GetWindowThreadProcessId(GetForegroundWindow(), NULL)
    );
    WORD layoutId = LOWORD(hkl);
    return layoutId == EN_US;
}

void ToggleEnglishOrNot(bool EnglishOrNot) {
    if (EnglishOrNot) {
        // Set KeyboardLayout to English.
		PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 0, EN_US);
    }
    else {
        // Set KeyboardLayout to Non English.
		if (IsEnglish()) {
			PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 
                INPUTLANGCHANGE_FORWARD, HKL_NEXT);
        }
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
    if (argc > 1) {
        // Toggle english if 1st arg is "-c";
        if (!_tcscmp(argv[1], _T("-c"))) {
            ToggleEnglishOrNot(true);
        }
        // Toggle non english if 1st arg is "-o" ;
        else if (!_tcscmp(argv[1], _T("-o"))) {
            ToggleEnglishOrNot(false);
        }
    } else {  // if no arg, print 1 for english, 2 for non english.
        cout << (IsEnglish() ? 1 : 2) << endl;
    }

    return 0;
}




