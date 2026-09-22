#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include "miniaudio.h"  // 包含 miniaudio 頭文件

class AudioManager {
public:
    // 初始化音效引擎
    static void initialize();
    static void shutdown();

    // 播放音符
    static void playNote(const std::string& note);

    // 播放音軌
    static void playTrack(const std::vector<std::string>& trackNotes);

    // 停止所有播放
    static void stopAll();

    // 模擬音效處理
    static void simulateAudioEffect();

private:
    static ma_engine engine;  // 引擎實例
};

#endif
