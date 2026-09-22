#include <iostream>
#include <limits>
#include "LoopStation.h"
#include "AudioManager.h"
#include "Utils.h"
#include "Track.h"
#include "miniaudio.c"
#include "AudioManager.cpp"
#include "LoopStation.cpp"
#include "Track.cpp"
#include "Utils.cpp"
using namespace std;

void showMenu() {
    Utils::printFormatted("Loop Station Menu", '=');
    cout << "1. Add Track\n";
    cout << "2. Record Note to Track\n";
    cout << "3. Clear Track\n";
    cout << "4. Start Playback\n";
    cout << "5. Delete Previous Note\n";
    cout << "6. Delete Track\n";
    cout << "7. Exit\n";
    cout << "Select an option: ";
}

void showWelcomeScreen() {
    Utils::printFormatted("Welcome to the Loop Station!", '=');
    cout << "Create and manage your music loops with ease.\n";
    cout << "You can add tracks, record notes, and play them back.\n";
    cout << "Let's get started!\n\n";
}

int main() {
    // Display the welcome screen
    showWelcomeScreen();

    // Initialize audio engine
    AudioManager::initialize();

    int totalBeats;
    cout << "Enter total beats (e.g., 4, 8, or 16): ";
    while (!(cin >> totalBeats) || (totalBeats != 4 && totalBeats != 8 && totalBeats != 16)) {
        cout << "Invalid input. Please enter 4, 8, or 16: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int bpm;
    cout << "Enter tempo (BPM): ";
    while (!(cin >> bpm) || bpm <= 0) {
        cout << "Invalid input. Please enter a positive BPM: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    LoopStation loopStation(totalBeats);
    loopStation.setTempo(bpm);

    int choice, trackIndex;
    string trackName, note, duration;

    while (true) {
        showMenu();
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid choice. Please select a valid option (1-7): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: {
                string trackName;
                cout << "Enter track name: ";
                cin >> trackName;
                loopStation.addTrack(trackName);  // 將音軌加入 LoopStation
                break;
            }
            case 2: {
                // Display current tracks
                loopStation.displayTracks();

                // Record note to track
                int trackIndex;
                std::string note;
                std::cout << "Enter track index: ";
                cin >> trackIndex;
                std::cout << "Enter note: ";
                cin >> note;

                // Default to "quarter" duration
                std::string duration = "quarter";

                // Ensure the call includes the duration
                loopStation.recordNoteToTrack(trackIndex - 1, note, duration);
                break;
            }
            case 3: {
                int trackIndex;
                cout << "Enter track index to clear: ";
                cin >> trackIndex;
                loopStation.clearTrack(trackIndex - 1);
                break;
            }
            case 4: {
                // 開始播放
                int loopCount;
                cout << "Enter number of loops: ";
                while (!(cin >> loopCount) || loopCount <= 0) {
                    cout << "Invalid input. Please enter a positive number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                loopStation.startPlayback(loopCount);
                break;
            }
            case 5: {
                // Display current tracks
                loopStation.displayTracks();

                // Remove the last note from a track
                int trackIndex;
                std::cout << "Enter track index to remove the last note: ";
                cin >> trackIndex;
                if (trackIndex > 0 && trackIndex <= loopStation.getTrackCount()) {
                    loopStation.removeLastNoteFromTrack(trackIndex - 1);
                } else {
                    std::cout << "Invalid track index.\n";
                }
                break;
            }
            case 6: {
                // Delete a track
                loopStation.displayTracks();
                int trackIndex;
                std::cout << "Enter track index to delete: ";
                cin >> trackIndex;
                loopStation.deleteTrack(trackIndex - 1);
                break;
            }
            case 7: {
                Utils::printFormatted("Goodbye!", '~');
                // 釋放音效引擎資源
                AudioManager::shutdown();
                return 0;
            }
            default: {
                cout << "Invalid choice. Try again!\n";
                break;
            }
        }

        Utils::delay(1000);  // 等待 1 秒
    }
}
