#pragma once

namespace audioManager
{
    enum MusicID
    {
        MUSIC_MENU,
        MUSIC_GAMEPLAY,
        MUSIC_COUNT
    };

    enum SfxID
    {
        SFX_JUMP_PLAYER,
        SFX_BUTTON_CLICK,
        SFX_PANEL,
        SFX_COUNT
    };

    void Init();
    void InitSound();
    void Update();
    void Close();

    void PlayMusic(MusicID id);
    void PauseMusic(MusicID id, bool pause);
    void StopMusic(MusicID id);

    void PlaySfx(SfxID id);
}