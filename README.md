# Farmbot Webots Project

## Overview

This repository contains a Webots simulation project for the Farmbot platform. It includes controller code, reusable libraries, and a sample world file with a tomato plant object. The project is organized to separate controller logic, low-level hardware-like libraries, and world assets so you can develop, build, and run experiments in Webots quickly.

Key components:
- controllers/Farmbot — main controller and build targets
- libraries/Farmbot_control — low-level drivers and helpers for base, arm, and gripper
- worlds/Farmbot.wbt — Webots world used to run the simulation

## Repository Structure

- [controllers/Farmbot](controllers/Farmbot): Controller source and Makefile
- [controllers/Farmbot/Makefile](controllers/Farmbot/Makefile) — build targets (release, emcc, etc.)
- [controllers/Farmbot/Farmbot.c](controllers/Farmbot/Farmbot.c) — main controller implementation
- [controllers/Farmbot/build](controllers/Farmbot/build) — build outputs (emcc/release)
- [libraries/Farmbot_control](libraries/Farmbot_control): Helpers and device implementations
- [libraries/Farmbot_control/include](libraries/Farmbot_control/include): Public headers (`arm.h`, `base.h`, `gripper.h`, `tiny_math.h`)
- [libraries/Farmbot_control/src](libraries/Farmbot_control/src): Source files (`arm.c`, `base.c`, `gripper.c`, `tiny_math.c`)
- [worlds/Farmbot.wbt](worlds/Farmbot.wbt): Webots world file for the Farmbot simulation
- [tomato_plant](tomato_plant): mesh/material assets used in the world

## Prerequisites

- Webots (https://cyberbotics.com/) — tested with a recent stable release. Install Webots and ensure `webots` is on your PATH if you want to launch from the command line.
- make, gcc/clang (for building native controllers)
- Optional: Emscripten SDK (if you need the `emcc` target to build WebAssembly versions). See the `controllers/Farmbot/Makefile` for emcc targets.
- Recommended on Windows: use WSL2, MSYS2, or an environment that provides `make` and a Unix-like toolchain.

## Build Instructions

1. Build the libraries (optional but recommended):

```bash
cd libraries
make
```

2. Build the Farmbot controller (release build):

```bash
cd controllers/Farmbot
make release
```

This will place the built controller binary in `controllers/Farmbot/build/release` (or a similar path configured by the Makefile).

3. (Optional) Build WebAssembly/emscripten target:

```bash
cd controllers/Farmbot
make emcc
```

Note: emcc builds require a configured Emscripten environment. The Makefile contains the emcc target and output paths under `controllers/Farmbot/build/emcc/`.

## Run the Simulation

Start Webots and open the world:

1. Open Webots and choose `File -> Open World` then select [worlds/Farmbot.wbt](worlds/Farmbot.wbt).
2. With the world loaded, select the `Farmbot` robot (or its controller node) and ensure the controller binary path points to the compiled controller in `controllers/Farmbot/build/release`.
3. Click the play button to run the simulation. Webots will start the controller process for the robot.

You can also run Webots from the command line:

```bash
webots worlds/Farmbot.wbt
```

If using a headless batch run (CI or automated experiments), consult Webots documentation for `--batch` options and ensure controllers are accessible in the runtime environment.

## Controller Details

- The main controller source is at [controllers/Farmbot/Farmbot.c](controllers/Farmbot/Farmbot.c).
- The controller uses helper modules provided in `libraries/Farmbot_control` (base, arm, gripper, tiny_math).
- The libraries expose C headers in `libraries/Farmbot_control/include` and implementations in `libraries/Farmbot_control/src`.

## Development Notes

- To add features to the controller, edit `controllers/Farmbot/Farmbot.c` and re-run `make release`.
- If you change function signatures in the libraries, update the headers in `libraries/Farmbot_control/include` and recompile dependent targets.
- For experimenting with sensors or new actuators, add or modify the appropriate device initialization in the world file and in the controller code.

## Troubleshooting

- Build fails on Windows: ensure you have a Unix-like toolchain (WSL2 or MSYS2) and that `make` and a C compiler are installed.
- Controller crashes on startup: run the controller binary directly from the command line to see error output, and check that the binary path in Webots matches the built binary location.
- Emscripten build issues: verify Emscripten SDK is activated (source `emsdk_env.sh`) and that `emcc` is on your PATH.

## Contributing

Contributions are welcome. Suggested workflow:

1. Fork the repository.
2. Create a feature branch for your changes.
3. Add or update code, headers, and tests as needed.
4. Run local builds and verify the simulation runs in Webots.
5. Open a pull request describing your changes.

Please include any relevant notes about required Webots versions, compiler toolchains, or environment setup in your PR description.

## License

This project does not include a license file. Add a LICENSE file to the repository to clarify reuse terms (e.g., MIT, Apache-2.0). If you want, I can add a suggested license.

## Contact

If you want help extending the project, running CI builds, or porting to a different platform, tell me what you'd like to do next and I can help.
