#include "AudioManager.h"
#include "miniaudio.c"

// 初始化音效引擎
ma_engine AudioManager::engine;

void AudioManager::initialize() {
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Audio engine initialized successfully." << std::endl;
}

void AudioManager::shutdown() {
    ma_engine_uninit(&engine);
    std::cout << "Audio engine shut down." << std::endl;
}

void AudioManager::playNote(const std::string& note) {
    std::string filename = "sounds/" + note + ".wav";  // 假設音符對應音效文件
    ma_result result = ma_engine_play_sound(&engine, filename.c_str(), NULL);

    if (result != MA_SUCCESS) {
        std::cerr << "Failed to play note: " << note << std::endl;
    } else {
        std::cout << "Playing note: " << note << std::endl;
    }
}

void AudioManager::playTrack(const std::vector<std::string>& trackNotes) {
    std::cout << "Starting track playback:\n";
    for (const auto& note : trackNotes) {
        playNote(note);
    }
    std::cout << "Track playback finished.\n";
}

void AudioManager::stopAll() {
    std::cout << "Stopping all audio playback (not implemented in miniaudio).\n";
}

void AudioManager::simulateAudioEffect() {
    std::cout << "Simulating audio effect (e.g., reverb, delay).\n";
}
