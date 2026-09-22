#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <vector>
#include <utility> // For std::pair

class Track {
private:
    std::string name;  // 音軌名稱
    std::vector<std::pair<std::string, std::string>> notes;  // 儲存錄製的音符和其持續時間
    bool isPlaying = false;  // 播放狀態

public:
    Track(const std::string& trackName);  // 初始化音軌
    void recordNote(const std::string& note, const std::string& duration);  // 錄製音符
    void clearTrack();  // 清除音軌內容
    void play();  // 播放音軌
    void stop();  // 停止播放
    std::string getName() const;  // 取得音軌名稱
    bool getIsPlaying() const;  // 取得播放狀態
    void displayNotes() const;  // 顯示音軌上的音符
    const std::vector<std::pair<std::string, std::string>>& getNotes() const;
    void removeLastNote();  // New method to remove the last note
};

#endif
