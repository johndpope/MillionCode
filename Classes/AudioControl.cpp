//
//  AudioControl.cpp
//  MillionCode
//
//  Created by 木村巧 on 2015/04/29.
//
//

#include "AudioControl.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace std;

namespace{
    // メモリに読み込むSEファイルの数（変更する際は最大32まで）
    static const int MAX = 5;
    string fileName;
    string seFileName[MAX];
    AudioControl &audioControl = AudioControl::getInstance();
    SimpleAudioEngine* simpleAudioEngine = SimpleAudioEngine::getInstance();
}

void AudioControl::createBgm(string filePath, float volume)
{
    fileName = filePath;
    simpleAudioEngine->preloadBackgroundMusic(fileName.c_str());
    simpleAudioEngine->setBackgroundMusicVolume(volume);
}

void AudioControl::playBgm(bool loop)
{
    simpleAudioEngine->playBackgroundMusic(fileName.c_str(), loop);
}

void AudioControl::stopBgm()
{
    simpleAudioEngine->stopBackgroundMusic();
}

void AudioControl::createSe(std::string filePath, float volume)
{
    seFileName[0] = filePath;
    simpleAudioEngine->preloadEffect(seFileName[0].c_str());
    simpleAudioEngine->setEffectsVolume(1.0f);
}

void AudioControl::createSe(string filePath, const float volume, int num)
{
    seFileName[num] = filePath;
    simpleAudioEngine->preloadEffect(seFileName[0].c_str());
    simpleAudioEngine->setEffectsVolume(1.0f);
}

void AudioControl::playSe(string filePath)
{
    for (int i; i < MAX; ++i)
    {
        if(filePath == seFileName[i])
        {
            simpleAudioEngine->playEffect(seFileName[i].c_str());
        }
    }
}

void AudioControl::stopSe(string filePath)
{
    for (int i; i < MAX; ++i)
    {
        if(filePath == seFileName[i])
        {
            simpleAudioEngine->playEffect(seFileName[i].c_str());
        }
    }
}

void AudioControl::unloadSe()
{
    for (int i; i < MAX; ++i)
    {
        simpleAudioEngine->unloadEffect(seFileName[i].c_str());
    }
}
