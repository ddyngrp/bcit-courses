/*
	MODULE: model.h

	PURPOSE: Window model

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
*/

#ifndef _MODEL_H_
#define _MODEL_H_

#include <string.h>

class Model {
    enum { TEXT_SIZE = 20 };
public:
    Model(char const * str) {
        SetText(str);
        _text[TEXT_SIZE] = '\0';
    }

    void SetText(char const * str) {
        strncpy_s(_text, str, TEXT_SIZE);
    }

    char const * GetText() const { return _text; }
    int GetLen() const { return (int)strlen(_text); }

private:
    char _text[TEXT_SIZE + 1];
};

#endif