#pragma once

namespace audioManager
{
    enum MusicID
    {
        MUSIC_MENU,
        MUSIC_GAMEPLAY,
        MUSIC_COUNT
    };

    void Init();
    void InitMusic();
    void Update();
    void Close();

    void PlayMusic(MusicID id);
    void PauseMusic(MusicID id, bool pause);
    void StopMusic(MusicID id);
}