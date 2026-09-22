# Small Loop Station

A C++ console application for creating short, sample-based musical loops. Users organize notes into named tracks, set a tempo, and play the tracks together over a fixed number of beats.

Developed as a **Programming I final project**, Small Loop Station connects introductory programming concepts with an interactive audio application. Its educational focus is the relationship between data representation, program structure, and audible behavior.

## Project at a Glance

| Aspect | Description |
| --- | --- |
| Language | C++ |
| Interface | Interactive console menu |
| Audio library | Bundled miniaudio v0.11.21 |
| Audio assets | 46 WAV samples covering pitched notes, bass, and percussion |
| Core concepts | Classes, encapsulation, STL containers, modular arithmetic, input validation, and library integration |
| Scope | An in-memory, sample-based sequencer for a course project |

## Purpose and Features

The project explores how symbolic input, such as `C4` or `Kick1`, can become a repeating musical pattern. Users select 4, 8, or 16 beats per loop and a positive BPM, create tracks, and append sample names to each track. During playback, each nonempty track contributes one sample trigger per beat.

The menu supports:

- Creating and deleting named tracks.
- Appending notes to a selected track and displaying its contents.
- Removing the most recently added note or clearing an entire track.
- Playing a specified number of loops at the selected tempo.

Here, **recording a note means entering a sample name into a sequence**. The program does not record microphone input.

## Design and Implementation

| Component | Responsibility |
| --- | --- |
| `main.cpp` | Collects user input, presents menu options, and coordinates startup and shutdown. |
| `LoopStation` | Owns tracks, manages editing operations, and schedules sample triggers by beat. |
| `Track` | Stores a track name and an ordered sequence of note/duration pairs. |
| `AudioManager` | Initializes miniaudio, maps note names to WAV paths, and requests playback. |
| `Utils` | Formats console messages and provides a delay helper. |

### Data Representation

`LoopStation` stores tracks in a `std::vector<Track>`. Each `Track` stores notes in a `std::vector<std::pair<std::string, std::string>>`, pairing a sample identifier with a duration label. This supports appending notes, removing the last note, clearing a sequence, and iterating through track contents.

The console uses one-based track numbers, while internal operations use zero-based indices. Track-management methods check index bounds before accessing the vector.

### Looping and Tempo

For each beat, the playback loop selects a note from each nonempty track using:

```cpp
int noteIndex = cycle % notes.size();
```

This lets a short sequence repeat within a longer loop. A two-note track containing `Kick1` and `Snare1` produces `Kick1, Snare1, Kick1, Snare1` across four beats. Each new loop restarts the sequence at index zero.

The intended interval between beats is `60.0 / BPM` seconds: 0.5 seconds at 120 BPM. Sample requests for all tracks are issued consecutively on each beat, while miniaudio handles playback and mixing. The application does not guarantee sample-accurate alignment.

### Audio Integration and Implementation Scope

`AudioManager` translates an identifier such as `C4` into `sounds/C4.wav` and calls miniaudio to play the file. Audio-engine initialization failure ends the program, while a failed sample request prints an error. Normal exit releases the engine.

The project-specific code implements the console interface, track model, editing operations, and beat loop. **miniaudio is a third-party dependency** providing audio decoding and playback; the project does not implement its own audio engine.

## Build and Run

Use a C++ compiler with C++11 support and an available audio output device. From the project directory, run:

```powershell
g++ -std=c++11 main.cpp -o SmallLoopStation.exe
.\SmallLoopStation.exe
```

The build command was verified with **MinGW GCC 6.3.0 on Windows**. Other platforms have not been verified. Run the executable from the project directory so the relative `sounds/` paths resolve correctly.

The current source layout directly includes implementation files from `main.cpp`. Compile **only `main.cpp`**, rather than every `.cpp` file together, to avoid duplicate definitions. Generated executables are excluded from Git.

## Example Walkthrough

1. Enter `4` beats and `120` BPM.
2. Choose **1. Add Track** and name the track `Drums`.
3. Choose **2. Record Note to Track**, select track `1`, and enter `Kick1`.
4. Repeat the previous step to append `Snare1` to track `1`.
5. Add a second track named `Melody`, then append `C4`, `E4`, `G4`, and `E4` to track `2` using the same menu option.
6. Choose **4. Start Playback** and enter `2` loops.
7. After playback finishes, remove a track's last note or clear its contents, then play again to compare the result.
8. Choose **7. Exit** to shut down the audio engine.

Use sample names exactly as they appear in `sounds/`, without `.wav`. Other examples include `BassC2`, `Hihat1`, and `Clap1`. Track names and sample names are read as single words.

## Programming Concepts Demonstrated

- **Object-oriented decomposition:** Track storage, loop control, audio access, and console utilities have distinct responsibilities.
- **Data structures applied to an interactive task:** Vectors support editable collections of tracks and notes; pairs associate notes with duration metadata.
- **Algorithmic reasoning:** Modulo indexing implements repetition, and a tempo calculation connects numerical input to playback intervals.
- **Library integration:** A dedicated wrapper translates application-level sample names into miniaudio playback calls.
- **Basic defensive programming:** The program validates main-menu choices, supported loop lengths, positive BPM and loop counts, and track-index bounds.

These points are observable in the source. They describe the implementation rather than asserting unmeasured performance results.

## Limitations and Further Development

| Current limitation | Possible improvement |
| --- | --- |
| Timing uses a busy-wait loop around `std::clock()`, consuming CPU and limiting timing precision. | Introduce a monotonic clock and nonblocking scheduling; measure drift. |
| The menu waits for playback to finish and offers no interactive stop command during playback. | Separate playback from input handling and provide a safe stop mechanism. |
| Duration labels are stored, but the menu always records `quarter` and playback uses a fixed interval. | Schedule explicit durations and rests. |
| Tracks and notes exist only in memory. | Add project saving/loading and, separately, rendered audio export. |
| Some numeric input paths do not recover from malformed input; sample names are not checked before playback. | Centralize input validation and display available samples. |
| Implementation files are directly included rather than compiled separately. | Adopt separate compilation and a reproducible build configuration. |
| `stopAll()` and `simulateAudioEffect()` only print messages. | Implement sound-instance control and effects before exposing them as features. |

There is no automated test suite or published timing benchmark. The walkthrough provides a manual review scenario; audible output and timing should be checked on the machine running the application.

## Repository Layout

```text
Small-Loop-Station/
|-- main.cpp
|-- AudioManager.h / AudioManager.cpp
|-- LoopStation.h / LoopStation.cpp
|-- Track.h / Track.cpp
|-- Utils.h / Utils.cpp
|-- miniaudio.h / miniaudio.c
|-- sounds/                  # WAV samples used by the sequencer
|-- .gitignore
`-- README.md
```

## Third-Party Materials

The bundled miniaudio files retain their original copyright and licensing notices. The repository does not currently document the WAV samples' origins or redistribution terms, and no project-wide license is declared.
