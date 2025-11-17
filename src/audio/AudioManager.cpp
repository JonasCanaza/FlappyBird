#include "AudioManager.h"

#include "BorjaLib.h"

namespace audioManager
{
    static int playMusicID;
    static snd::AudioData musicTracks[MusicID::MUSIC_COUNT];

    void Init() // IMPORTANT: ONLY DO "Init();" IN "Game.cpp"
    {
        snd::StartAudioDevice();
        playMusicID = 0;
    }

    void InitMusic()
    {
        musicTracks[MUSIC_MENU].file = "res/audio/music/Menu.ogg";
        musicTracks[MUSIC_MENU].name = "Menu music";
        musicTracks[MUSIC_MENU].id = snd::InitAudioData(musicTracks[MUSIC_MENU]);

        musicTracks[MUSIC_GAMEPLAY].file = "res/audio/music/Gameplay.ogg";
        musicTracks[MUSIC_GAMEPLAY].name = "Gameplay music";
        musicTracks[MUSIC_GAMEPLAY].id = snd::InitAudioData(musicTracks[MUSIC_GAMEPLAY]);
    }

    void Update()
    {
        //std::cout << snd::IsPlaying(musicTracks[MUSIC_MENU].id) << std::endl;
        //std::cout << snd::IsPlaying(musicTracks[MUSIC_GAMEPLAY].id) << std::endl;

        //std::cout << musicTracks[MUSIC_MENU].id << std::endl;
        //std::cout << musicTracks[MUSIC_GAMEPLAY].id << std::endl;

        //if (!snd::IsPlaying(playID))
        //{
        //    if (playID != 0)
        //    {
        //        snd::Play(playID);
        //    }
        //}
    }

    void Close() // IMPORTANT: ONLY DO "Close();" IN "game.cpp"
    {
        for (int i = 0; i < MUSIC_COUNT; i++)
        {
            snd::DeInit(musicTracks[i]);
        }

        snd::EndAudioDevice();
    }

    void PlayMusic(MusicID id)
    {
        switch (id)
        {
        case audioManager::MUSIC_MENU:

            snd::Play(musicTracks[MUSIC_MENU].id);
            playMusicID = musicTracks[MUSIC_MENU].id;

            break;
        case audioManager::MUSIC_GAMEPLAY:

            snd::Play(musicTracks[MUSIC_GAMEPLAY].id);
            playMusicID = musicTracks[MUSIC_GAMEPLAY].id;

            break;
        default:

            // NO MORE LOADED MUSIC

            break;
        }
    }

    void StopMusic(MusicID id)
    {
        switch (id)
        {
        case audioManager::MUSIC_MENU:

            snd::Stop(musicTracks[MUSIC_MENU].id);

            break;
        case audioManager::MUSIC_GAMEPLAY:

            snd::Stop(musicTracks[MUSIC_GAMEPLAY].id);

            break;
        default:

            // NO MORE LOADED MUSIC

            break;
        }
    }
}