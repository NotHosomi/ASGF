#pragma once
#include "Text.h"

class TextBox :
    public Text
{
public:
    TextBox(const std::string& sFont, int pt, const std::string& sText = "");
    ~TextBox();

    void SetTextWidth(int nWidth);
    int GetTextWidth();
private:
    int m_nTextWidth = 100;
    bool Generate() override;
};

