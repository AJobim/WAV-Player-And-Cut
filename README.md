# WAV Player and Cutter

This project is a simple C-based program that allows the user to interact with WAV audio files. It enables users to play a WAV file and also cut a specific segment from the audio to create a new WAV file. The program works in a console environment and uses the Windows `PlaySound` API for audio playback.

## Features

- **Play WAV File**: Allows the user to play a specified WAV file.
- **Cut Audio Segment**: Lets the user specify a start and end time in seconds to cut a segment from the WAV file and save it as a new file.
- **Cross-Platform Audio Playback**: Uses the Windows `PlaySound` API for audio playback.

## Prerequisites

- A Windows machine with a C compiler installed.
- The program uses `windows.h` and `mmsystem.h`, which are available in the Windows development environment.
- Basic knowledge of C programming to compile and run the program.
