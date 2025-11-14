#include "background/BackgroundManager.h"

#include "BorjaLib.h"

namespace backgroundManager
{
	static float aspect = rend::windowSize.x / rend::windowSize.y;

	static drw::SpriteData back;
	static float backSpeed;

	static drw::SpriteData mid;
	static float midSpeed;

	static drw::SpriteData front;
	static float frontSpeed;

	static drw::SpriteData foreground;
	static float foregroundSpeed;

	static void DrawLayer(drw::SpriteData& layer);

	void Init()
	{
		back.file = "res/sprites/backgrounds/back.png";
		back.size = { aspect, 1.0f };
		back.offset = { 0.0f, 0.0f };
		backSpeed = 0.05f;
		back.id = drw::InitSpriteData(back);

		mid.file = "res/sprites/backgrounds/mid.png";
		mid.size = { aspect, 1.0f };
		mid.offset = { 0.0f, 0.0f };
		midSpeed = 0.10f;
		mid.id = drw::InitSpriteData(mid);

		front.file = "res/sprites/backgrounds/front.png";
		front.size = { aspect, 1.0f };
		front.offset = { 0.0f, 0.0f };
		frontSpeed = 0.20f;
		front.id = drw::InitSpriteData(front);

		foreground.file = "res/sprites/backgrounds/foreground.png";
		foreground.size = { aspect, 1.0f };
		foreground.offset = { 0.0f, 0.0f };
		foregroundSpeed = 0.35f;
		foreground.id = drw::InitSpriteData(foreground);
	}

	void Update()
	{
		back.offset.x -= backSpeed * rend::deltaTime;
		mid.offset.x -= midSpeed * rend::deltaTime;
		front.offset.x -= frontSpeed * rend::deltaTime;
		foreground.offset.x -= foregroundSpeed * rend::deltaTime;

		if (back.offset.x <= -aspect)
		{
			back.offset.x += aspect;
		}

		if (mid.offset.x <= -aspect)
		{
			mid.offset.x += aspect;
		}

		if (front.offset.x <= -aspect)
		{
			front.offset.x += aspect;
		}

		if (foreground.offset.x <= -aspect)
		{
			foreground.offset.x += aspect;
		}
	}

	void Draw()
	{
		DrawLayer(back);
		DrawLayer(mid);
		DrawLayer(front);
		DrawLayer(foreground);
	}

	static void DrawLayer(drw::SpriteData& layer)
	{
		drw::Sprite(drw::spriteDataList[layer.id], { 0.5f, 0.5f }, layer.size, layer.offset);
		drw::Sprite(drw::spriteDataList[layer.id], { 0.5f, 0.5f }, layer.size, { layer.offset.x + aspect, layer.offset.y });
	}
}
