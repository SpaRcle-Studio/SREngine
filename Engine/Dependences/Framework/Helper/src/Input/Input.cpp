//
// Created by Nikita on 17.11.2020.
//

#include "Input/Input.h"

int Framework::Helper::Input::GetKeyPressedId() {
    BYTE *arr = new BYTE[256];
    int result = 0;

    memset(arr, 0, sizeof(256));
    GetKeyState(0);
    if (GetKeyboardState(arr)) {
        for (int i = 0; i < 256; i++)
            if (arr[i] >> 7 != 0) {
                result = i;
                break;
            }
    }

    delete[] arr;
    return result;
}

bool Framework::Helper::Input::BaseGetKey(Framework::Helper::KeyCode key) {
    BYTE* arr = new BYTE[256];
    bool result = false;

    memset(arr, 0, sizeof(256));
    GetKeyState(0);
    if (GetKeyboardState(arr)) {
        int temp = (int)arr[(int)key];
        temp >>= 7;
        result = (bool)temp;
    }

    delete[] arr;

    return result;
}
