#include "interface/Button.h"

#include "BorjaLib.h"

namespace button
{
	static btn::Button templateButton;

	static const vec::Vector2 BUTTON_SIZE = { 0.3f, 0.085f };
	static const float FONT_SIZE = 0.075f;

	static drw::SpriteData normalTexture;
	static drw::SpriteData hoverTexture;

	void Init()
	{
		normalTexture.file = "res/sprites/ui/ButtonNormal.png";
		normalTexture.id = drw::InitSpriteData(normalTexture);

		hoverTexture.file = "res/sprites/ui/ButtonHover.png";
		hoverTexture.id = drw::InitSpriteData(hoverTexture);

		templateButton.size = BUTTON_SIZE;
		templateButton.textData.fontSize = FONT_SIZE;
	}

	void Close()
	{
		drw::DeInitSpriteData(normalTexture);
		drw::DeInitSpriteData(hoverTexture);
	}

	btn::Button GetTemplate()
	{
		return templateButton;
	}

	int GetNormalTextureID()
	{
		return normalTexture.id;
	}

	int GetHoverTextureID()
	{
		return hoverTexture.id;
	}
}