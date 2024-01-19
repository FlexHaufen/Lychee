# Lychee  
A **simple**, **fast** & **lightweight** game engine.

<img src="resource/images/Lychee.svg" height="100">

## Intention
- Lychee should be a free (unless i decide else)
- It should be easy to use and should have a simple user-interface
- It should run on every patato

## Dependencies
- [SFML](https://www.sfml-dev.org/index.php) 
- [spdlog](https://github.com/gabime/spdlog)
- [ImGui](https://github.com/ocornut/imgui)
- [ImGUi-SFML](https://github.com/SFML/imgui-sfml)

## Setup
### Requirements
- Cmake Version **Version 3.24.1** or higher
- MSVC 19 or higher

### Setup Repo
1. Clone
    ```bash 
    git clone git@github.com:FlexHaufen/Lychee.git
    ```

2. Setup submodules in ./Lychee
    ```shell
    git submodule update --init --recursive
    ```
    ```shell
    git submodule update --recursive --remote
    ```

    ImGui Has to be on docking branch

4. Configure Cmake
    - In VScode press F1 - Type Cmake Configure - Press Enter
    - Select "Visual Studio Compiler 2022 Release - amd64" - Press Enter

### Build
- To Build Press F7 - **NOTE:** By default it will build a Debug-Build

### Run
To Run the .exe file via F5 you first need to configure a ```launch.json``` in your ```.vscode``` folder. Like the example below

- To Run Press F5 - **NOTE:** By default it will run a Release-Build

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Release",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/bin/release/Lychee.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "console": "externalTerminal"
        },
        {
            "name": "Debug",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/bin/debug/Lychee.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "console": "externalTerminal"
        }
    ]
}
```



## Acknowledgements
 - [Hazel Engine](https://github.com/TheCherno/Hazel)
 - [Game Engine Series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
 - [ImGui Theme by @Trippasch](https://github.com/Trippasch)