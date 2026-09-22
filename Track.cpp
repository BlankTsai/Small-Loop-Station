#include "Track.h"
#include <iostream>

Track::Track(const std::string& trackName) : name(trackName), isPlaying(false) {}

void Track::recordNote(const std::string& note, const std::string& duration) {
    notes.emplace_back(note, duration);  // Record note with its duration
}

void Track::clearTrack() {
    notes.clear();  // 清除音軌的所有音符
    std::cout << name << " track cleared.\n";
}

void Track::displayNotes() const {
    if (notes.empty()) {
        std::cout << "No notes recorded.";
    } else {
        for (const auto& note : notes) {
            std::cout << note.first << "(" << note.second << ") ";
        }
    }
}

std::string Track::getName() const {
    return name;  // 返回音軌名稱
}

bool Track::getIsPlaying() const {
    return isPlaying;  // 返回音軌是否正在播放
}

void Track::play() {
    if (notes.empty()) {
        std::cout << name << " track is empty.\n";  // 如果音軌沒有音符，無法播放
        return;
    }
    isPlaying = true;  // 設定播放狀態為 true
    std::cout << "Playing " << name << " track:\n";
    displayNotes();  // 顯示音軌上的音符
}

void Track::stop() {
    isPlaying = false;  // 設定播放狀態為 false
    std::cout << "Stopped playing " << name << " track.\n";
}

const std::vector<std::pair<std::string, std::string>>& Track::getNotes() const {
    return notes;
}

void Track::removeLastNote() {
    if (!notes.empty()) {
        notes.pop_back();  // Remove the last note
        std::cout << "Last note removed.\n";
    } else {
        std::cout << "No notes to remove.\n";
    }
}
