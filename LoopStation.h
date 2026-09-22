#ifndef LOOPSTATION_H
#define LOOPSTATION_H

#include <string>
#include <vector>
#include "Track.h"  // 包含 Track 類別的頭文件

class LoopStation {
public:
    LoopStation(int totalBeats);
    void addTrack(const std::string& trackName);
    void recordNoteToTrack(int trackIndex, const std::string& note, const std::string& duration);
    void clearTrack(int trackIndex);
    void startPlayback(int loopCount);
    void stopPlayback();
    void setTempo(int bpm);
    void displayTracks() const;
    void removeLastNoteFromTrack(int trackIndex);  // New method to remove the last note
    int getTrackCount() const { return tracks.size(); }  // Helper method to get track count
    void deleteTrack(int trackIndex);  // New method to delete a track

private:
    int totalBeats;
    int currentBeat;
    std::vector<Track> tracks;  // 改為儲存 Track 物件
    bool isPlaying;  // 新增的布爾型變量
    int tempo;  // 新增的變量
};

#endif
