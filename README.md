# Snake & Rabbit

A modern variation of the classic Snake game, written in **C** using **raylib**.

The rabbit moves when the snake gets close, making it more difficult to catch than ordinary food. The game includes a CRT-style shader, native desktop builds, and a browser version compiled to WebAssembly.

## Play Online

The WebAssembly version runs directly in the browser through GitHub Pages:

**[Play Snake & Rabbit](https://umaidmalik.github.io/snake-rabbit/)**

## Screenshots
<img width="1243" height="937" alt="snake-rabbit" src="https://github.com/user-attachments/assets/1fa422cf-fd4c-4e75-8f9a-d8da31caac74" />

<img width="1200" height="938" alt="snake-rabbit-2" src="https://github.com/user-attachments/assets/02645c29-16b3-4498-bf2d-f08a5a18e06a" />


## Features

* Classic grid-based snake movement
* A rabbit that moves away when the snake approaches
* Keyboard and gamepad input
* Speed boost
* Pause and restart controls
* Score and high-score tracking
* CRT-inspired post-processing shader
* Native Linux and Windows builds
* WebAssembly browser build
* Automated CI/CD through GitHub Actions
* GitHub Releases for downloadable builds
* Automatic GitHub Pages deployment

## Controls

| Key               | Action                   |
| ----------------- | ------------------------ |
| Arrow Keys / WASD | Move the snake           |
| Spacebar          | Speed boost              |
| **P**             | Pause or resume          |
| **R**             | Restart the current game |
| **M**             | Return to the main menu  |
| **Esc**           | Close the desktop game   |

Gamepad controls are also supported.

See [GAME_MANUAL.md](GAME_MANUAL.md) for complete gameplay information.

## Scoring

* Earn one point for each rabbit eaten.
* The snake grows after every rabbit.
* The high score is tracked for the current session.
* The game ends when the snake collides with itself.

## Downloads

Prebuilt packages are available from the repository's **Releases** page.

Each tagged release includes:

* Linux x86-64 build
* Windows x86-64 build
* WebAssembly package

## Building from Source

### Requirements

* A C compiler
* GNU Make or Visual Studio 2022
* Git
* Emscripten SDK for WebAssembly builds

The required raylib source is downloaded by the CI workflow for WebAssembly builds. The native Premake configuration manages the project build structure.

### Linux

Generate the Makefiles:

```bash
cd build
./premake5 gmake
cd ..
```

Build the game:

```bash
make -j"$(nproc)"
```

Run it:

```bash
./bin/Debug/snake-rabbit
```

To build the release configuration:

```bash
make config=release_x64 -j"$(nproc)"
```

### Windows

Generate a Visual Studio 2022 solution:

```text
build-VisualStudio2022.bat
```

Open the generated `.sln` file and build either the `Debug` or `Release` configuration.

A MinGW build script is also included:

```text
build-MinGW-W64.bat
```

### WebAssembly

Install and activate the Emscripten SDK, then run:

```bash
./build-web.sh
```

Serve the generated files through HTTP:

```bash
cd bin/Web
python3 -m http.server 8080
```

Open:

```text
http://localhost:8080
```

The browser build output includes:

```text
bin/Web/
├── index.html
├── index.js
├── index.wasm
└── index.data
```

## Project Structure

```text
snake-rabbit/
├── .github/workflows/    # CI, release, and deployment workflows
├── build/                # Premake configuration and dependencies
├── include/              # Header files
├── resources/            # Textures and shaders
├── src/                  # C source files
├── web/                  # WebAssembly HTML shell
├── build-web.sh          # Local WebAssembly build script
├── GAME_MANUAL.md        # Detailed game instructions
└── README.md
```

## Technology

* C
* raylib
* GLSL
* Emscripten
* WebAssembly
* Premake
* GitHub Actions
* GitHub Pages

## License

See [LICENSE](LICENSE) for license information.

## Acknowledgements

Built with [raylib](https://www.raylib.com/), a simple and easy-to-use library for games programming.
