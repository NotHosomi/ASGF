#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include "RenderTexture.h"
#include "Colour.h"

typedef struct _TTF_Font TTF_Font;

class Text : public RenderTexture
{
public:
	Text(const std::string& sFont, int pt, const std::string& sText = "");
	Text(const Text& other);
	Text(Text&& other);
	~Text();

	static void LoadFont(const std::string& pRenderer, int pt);
	static void FreeFonts();

	bool SetText(const std::string& sText);
	bool SetFont(const std::string& sFontName, int pt);

	void SetColour(const Colour& col) override;
	void SetColour(uint8_t r, uint8_t g, uint8_t b) override;
	void SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
	void SetAlpha(Uint8 alpha) override;

protected:
	static std::map<std::pair<std::string, int>, TTF_Font*> ms_mFonts;
	TTF_Font* m_pFont = nullptr;
	std::string m_sText;

	virtual bool Generate();
	bool FetchFont(const std::string& sFontName, int pt);
};