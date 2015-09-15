//
//  AudioControl.h
//  MillionCode
//
//  Created by 木村巧 on 2015/04/29.
//
//

#ifndef __MillionCode__AudioControl__
#define __MillionCode__AudioControl__

#include <iostream>
#include <cocos2d.h>
#include "SimpleAudioEngine.h"

class AudioControl
{
public:
    // 音楽ファイルの読み込み（BGM用）
    static void createBgm(std::string filePath, const float volume);
    // BGMの再生
    static void playBgm(bool loop);
    // BGMの停止
    static void stopBgm();
    // 音楽ファイルの読み込み(SE用）
    static void createSe(std::string filePath, const float volume);
    static void createSe(std::string filePath, const float volume, int num);
    // SEの再生
    static void playSe(std::string filePath);
    // SEの停止
    static void stopSe(std::string filePath);
    // createSeで保持しているファイルをメモリから解放する
    static void unloadSe();

public:
    static AudioControl &getInstance(){
    	static AudioControl instance;
    	return instance;
    }
private:
    AudioControl(){}
    AudioControl(const AudioControl &other){}
    AudioControl &operator=(const AudioControl &other){}

};

#endif /* defined(__MillionCode__AudioControl__) */
