#pragma once

namespace btn
{
	struct Button;
}

namespace button
{
	void Init();
	void Close();

	btn::Button GetTemplate();
	int GetNormalTextureID();
	int GetHoverTextureID();
}