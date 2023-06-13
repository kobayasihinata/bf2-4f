#include "PadInput.h"

char PAD_INPUT::now_key[BUTTONS];
char PAD_INPUT::old_key[BUTTONS];
XINPUT_STATE PAD_INPUT::input;
Stick PAD_INPUT::r_stick;
Stick PAD_INPUT::l_stick;