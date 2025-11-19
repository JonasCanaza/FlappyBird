#include "AudioManager.h"

#include "BorjaLib.h"

namespace audioManager
{
    static int playMusicID;
    static MusicID currentID;

    struct MusicData
    {
        snd::AudioData audio = {};
        bool isPause = false;
    };

    struct SfxData
    {
        std::string sourceFile;
        std::vector<snd::AudioData> instances;
    };

    static MusicData musicTracks[MusicID::MUSIC_COUNT];
    static SfxData sfxTracks[SfxID::SFX_COUNT];

    static void InitMusic();
    static void InitSfx();

    void Init() // IMPORTANT: ONLY DO "Init();" IN "Game.cpp"
    {
        snd::StartAudioDevice();
        playMusicID = 0;
        currentID = MUSIC_MENU;
    }

    void InitSound()
    {
        InitMusic();
        InitSfx();
    }

    void Update()
    {
        if (musicTracks[currentID].isPause)
        {
            return;
        }

        if (!IsSoundPlaying(snd::audioDataList[playMusicID].sound))
        {
            snd::Play(playMusicID);
        }
    }
    
    void Close() // IMPORTANT: ONLY DO "Close();" IN "Game.cpp"
    {
        for (int i = 0; i < MUSIC_COUNT; i++)
        {
            snd::DeInit(musicTracks[i].audio);
        }

        for (int i = 0; i < SFX_COUNT; i++)
        {
            for (int j = 0; j < static_cast<int>(sfxTracks[i].instances.size()); j++)
            {
                snd::DeInit(sfxTracks[i].instances[j]);
            }

            sfxTracks[i].instances.clear();
        }

        snd::EndAudioDevice();
    }

    void PlayMusic(MusicID id)
    {
        switch (id)
        {
        case audioManager::MUSIC_MENU:

            snd::Play(musicTracks[MUSIC_MENU].audio.id);
            playMusicID = musicTracks[MUSIC_MENU].audio.id;
            currentID = MUSIC_MENU;
            musicTracks[MUSIC_MENU].isPause = false;

            break;
        case audioManager::MUSIC_GAMEPLAY:

            snd::Play(musicTracks[MUSIC_GAMEPLAY].audio.id);
            playMusicID = musicTracks[MUSIC_GAMEPLAY].audio.id;
            currentID = MUSIC_GAMEPLAY;
            musicTracks[MUSIC_GAMEPLAY].isPause = false;

            break;
        default:

            // NO MORE LOADED MUSIC

            break;
        }
    }

    void PauseMusic(MusicID id, bool pause)
    {
        switch (id)
        {
        case audioManager::MUSIC_MENU:

            snd::Pause(musicTracks[MUSIC_MENU].audio.id, pause);

            if (pause)
            {
                musicTracks[MUSIC_MENU].isPause = true;
            }
            else
            {
                musicTracks[MUSIC_MENU].isPause = false;
            }

            break;
        case audioManager::MUSIC_GAMEPLAY:

            snd::Pause(musicTracks[MUSIC_GAMEPLAY].audio.id, pause);

            if (pause)
            {
                musicTracks[MUSIC_GAMEPLAY].isPause = true;
            }
            else
            {
                musicTracks[MUSIC_GAMEPLAY].isPause = false;
            }

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

            snd::Stop(musicTracks[MUSIC_MENU].audio.id);

            break;
        case audioManager::MUSIC_GAMEPLAY:

            snd::Stop(musicTracks[MUSIC_GAMEPLAY].audio.id);

            break;
        default:

            // NO MORE LOADED MUSIC

            break;
        }
    }

    void PlaySfx(SfxID id)
    {
        SfxData& track = sfxTracks[id];

        bool played = false;

        for (int i = 0; i < static_cast<int>(track.instances.size()); i++)
        {
            if (!IsSoundPlaying(track.instances[i].sound))
            {
                snd::Play(track.instances[i].id);
                played = true;

                break;
            }
        }

        if (!played)
        {
            snd::AudioData newAudio = {};
            newAudio.file = track.sourceFile;
            newAudio.id = snd::InitAudioData(newAudio);

            snd::Play(newAudio.id);

            track.instances.push_back(newAudio);
        }

        for (int i = 0; i < static_cast<int>(track.instances.size());)
        {
            if (!IsSoundPlaying(track.instances[i].sound) && i != static_cast<int>(track.instances.size()) - 1)
            {
                snd::DeInit(track.instances[i]);
                track.instances.erase(track.instances.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }

    static void InitMusic()
    {
        musicTracks[MUSIC_MENU].audio.file = "res/audio/music/Menu.ogg";
        musicTracks[MUSIC_MENU].audio.name = "Menu music";
        musicTracks[MUSIC_MENU].audio.id = snd::InitAudioData(musicTracks[MUSIC_MENU].audio);

        musicTracks[MUSIC_GAMEPLAY].audio.file = "res/audio/music/Gameplay.ogg";
        musicTracks[MUSIC_GAMEPLAY].audio.name = "Gameplay music";
        musicTracks[MUSIC_GAMEPLAY].audio.id = snd::InitAudioData(musicTracks[MUSIC_GAMEPLAY].audio);
    }

    static void InitSfx()
    {
        sfxTracks[SFX_JUMP_PLAYER].sourceFile = "res/audio/sfx/player/Jump.wav";
    }
}