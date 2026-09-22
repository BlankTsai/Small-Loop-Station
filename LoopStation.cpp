#include "LoopStation.h"
#include "AudioManager.h"
#include <iostream>
#include <ctime>  // For std::clock

LoopStation::LoopStation(int totalBeats) : currentBeat(0), totalBeats(totalBeats) {}

void LoopStation::addTrack(const std::string& trackName) {
    tracks.emplace_back(trackName);  // Add the new track
    displayTracks();  // Display the current tracks after adding a new one
}

void LoopStation::recordNoteToTrack(int trackIndex, const std::string& note, const std::string& duration) {
    if (trackIndex >= 0 && trackIndex < tracks.size()) {
        tracks[trackIndex].recordNote(note, duration);
    } else {
        std::cout << "Invalid track index.\n";
    }
}

void LoopStation::clearTrack(int trackIndex) {
    if (trackIndex >= 0 && trackIndex < tracks.size()) {
        tracks[trackIndex].clearTrack();  // 使用 Track 的 clearTrack 方法
    } else {
        std::cout << "Invalid track index.\n";
    }
}

void LoopStation::startPlayback(int loopCount) {
    isPlaying = true;
    std::cout << "Starting playback...\n";
    double quarterBeatDuration = 60.0 / tempo;  // Duration of a quarter note
    double eighthBeatDuration = quarterBeatDuration / 2;  // Duration of an eighth note

    for (int loop = 0; loop < loopCount && isPlaying; ++loop) {
        std::cout << "Loop " << loop + 1 << " of " << loopCount << ":\n";
        for (int cycle = 0; cycle < totalBeats; ++cycle) {
            // Play all tracks simultaneously for each beat
            for (auto& track : tracks) {
                const auto& notes = track.getNotes();
                if (!notes.empty()) {
                    // Use modulo to loop through notes
                    int noteIndex = cycle % notes.size();
                    const auto& note = notes[noteIndex].first;
                    const auto& duration = notes[noteIndex].second;

                    // Play the note
                    AudioManager::playNote(note);
                }
            }

            // Determine the duration to wait based on the longest note's duration
            double beatDuration = quarterBeatDuration;  // Default to quarter beat duration

            // Wait for the duration of the beat
            std::clock_t start_time = std::clock();
            while (std::clock() < start_time + beatDuration * CLOCKS_PER_SEC) {
                if (!isPlaying) {
                    std::cout << "Playback interrupted.\n";
                    return;
                }
            }
        }
    }
    isPlaying = false;
    std::cout << "Playback finished.\n";
}

void LoopStation::stopPlayback() {
    isPlaying = false;  // 設置播放狀態為 false
    std::cout << "Playback stopped.\n";
}

void LoopStation::displayTracks() const {
    std::cout << "Current Tracks:\n";
    for (size_t i = 0; i < tracks.size(); ++i) {
        std::cout << "Track " << i + 1 << ": " << tracks[i].getName() << "\n";
        std::cout << "Notes: ";
        tracks[i].displayNotes();  // Assuming displayNotes() prints notes
        std::cout << "\n";
    }
}

void LoopStation::setTempo(int bpm) {
    tempo = bpm;
}

void LoopStation::removeLastNoteFromTrack(int trackIndex) {
    if (trackIndex >= 0 && trackIndex < tracks.size()) {
        tracks[trackIndex].removeLastNote();
    } else {
        std::cout << "Invalid track index.\n";
    }
}

void LoopStation::deleteTrack(int trackIndex) {
    if (trackIndex >= 0 && trackIndex < tracks.size()) {
        tracks.erase(tracks.begin() + trackIndex);
        std::cout << "Track " << trackIndex + 1 << " deleted.\n";
    } else {
        std::cout << "Invalid track index.\n";
    }
}
