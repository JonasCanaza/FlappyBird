#include "background/BackgroundManager.h"

#include "BorjaLib.h"

namespace backgroundManager
{
	static drw::SpriteData back;
	static float backSpeed;

	static drw::SpriteData mid;
	static float midSpeed;

	static drw::SpriteData front;
	static float frontSpeed;

	static drw::SpriteData foreground;
	static float foregroundSpeed;

	static const vec::Vector2 DEFAULT_SPRITE_SIZE = { 1.0f, 1.0f };
	static const vec::Vector2 DEFAULT_SPRITE_OFFSET = { 0.0f, 0.0f };

	static const float BACK_SPEED = 0.05f;
	static const float MID_SPEED = 0.10f;
	static const float FRONT_SPEED = 0.20f;
	static const float FOREGROUND_SPEED = 0.35f;

	static const vec::Vector2 DRAW_POSITION = { 0.5f, 0.5f };

	static const float WRAP_LIMIT = -1.0f;
	static const float WRAP_OFFSET = 1.0f;

	static void DrawLayer(drw::SpriteData& layer);

	void Init()
	{
		back.file = "res/sprites/backgrounds/back.png";
		back.size = DEFAULT_SPRITE_SIZE;
		back.offset = DEFAULT_SPRITE_OFFSET;
		backSpeed = BACK_SPEED;
		back.id = drw::InitSpriteData(back);

		mid.file = "res/sprites/backgrounds/mid.png";
		mid.size = DEFAULT_SPRITE_SIZE;
		mid.offset = DEFAULT_SPRITE_OFFSET;
		midSpeed = MID_SPEED;
		mid.id = drw::InitSpriteData(mid);

		front.file = "res/sprites/backgrounds/front.png";
		front.size = DEFAULT_SPRITE_SIZE;
		front.offset = DEFAULT_SPRITE_OFFSET;
		frontSpeed = FRONT_SPEED;
		front.id = drw::InitSpriteData(front);

		foreground.file = "res/sprites/backgrounds/foreground.png";
		foreground.size = DEFAULT_SPRITE_SIZE;
		foreground.offset = DEFAULT_SPRITE_OFFSET;
		foregroundSpeed = FOREGROUND_SPEED;
		foreground.id = drw::InitSpriteData(foreground);
	}

	void Update()
	{
		back.offset.x -= backSpeed * rend::deltaTime;
		mid.offset.x -= midSpeed * rend::deltaTime;
		front.offset.x -= frontSpeed * rend::deltaTime;
		foreground.offset.x -= foregroundSpeed * rend::deltaTime;

		if (back.offset.x <= WRAP_LIMIT)
		{
			back.offset.x += WRAP_OFFSET;
		}

		if (mid.offset.x <= WRAP_LIMIT)
		{
			mid.offset.x += WRAP_OFFSET;
		}

		if (front.offset.x <= WRAP_LIMIT)
		{
			front.offset.x += WRAP_OFFSET;
		}

		if (foreground.offset.x <= WRAP_LIMIT)
		{
			foreground.offset.x += WRAP_OFFSET;
		}
	}

	void Draw()
	{
		DrawLayer(back);
		DrawLayer(mid);
		DrawLayer(front);
		DrawLayer(foreground);
	}

	void Close()
	{
		drw::DeInitSpriteData(back);
		drw::DeInitSpriteData(mid);
		drw::DeInitSpriteData(front);
		drw::DeInitSpriteData(foreground);
	}

	static void DrawLayer(drw::SpriteData& layer)
	{
		drw::Sprite(drw::spriteDataList[layer.id], DRAW_POSITION, layer.size, layer.offset);
		drw::Sprite(drw::spriteDataList[layer.id], DRAW_POSITION, layer.size, { layer.offset.x + WRAP_OFFSET, layer.offset.y });
	}
}
