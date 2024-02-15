# pong

A simple recreation of classic pong using a made-from-scratch 2D game engine.
![Pong](readme_assets/title_image.png)

## Building
Clone repo
```
git clone https://github.com/jonmgomez/pong.git
cd pong
```

Create build directory
```
mkdir build && cd build
```

Build with CMake
```
cmake ..
cmake --build . -j 10
```

Run with config file passed in
```
./Debug/pong.exe ../pong_config.json
```

Third Party Libraries:
- [AudioFile](https://github.com/adamstark/AudioFile) Used for reading in .wav files to be played
- [concurrentqueue](https://github.com/cameron314/concurrentqueue) A lock-free used to create the real-time logger and real time audio system.
- [fmt](https://github.com/fmtlib/fmt) Formatting library for log statements before being passed to the logger.
- [glfw](https://github.com/glfw/glfw) & [glew](https://github.com/nigels-com/glew) For better communication with OpenGL
- [glm](https://github.com/g-truc/glm) Math library with great compatibility with OpenGL
- [json](https://github.com/nlohmann/json) For parsing JSON scene and config files.
- [portaudio](https://github.com/PortAudio/portaudio) Main audio driver
- [spdlog](https://github.com/gabime/spdlog) Logging library
- [stb](https://github.com/nothings/stb) Utility library for loading in image files, and parsing true type font files
