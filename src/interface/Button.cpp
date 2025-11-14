#include "interface/Button.h"

#include "BorjaLib.h"

namespace button
{
	static btn::Button templateButton;

	void Init()
	{
		templateButton.size = { 0.450f, 0.085f };
		templateButton.textData.fontSize = 0.075f;
		templateButton.useSprite = false;
		templateButton.activeColor = SEMITRANSPARENT_B;
		templateButton.mainColor = SEMITRANSPARENT_B;
		templateButton.hoveredColor = SEMITRANSPARENT_B;
	}

	btn::Button GetTemplate()
	{
		return templateButton;
	}
}