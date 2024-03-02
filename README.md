# Lychee  
A **simple**, **fast** & **lightweight** voxel engine written in pure **C++**.

<img src="resource/images/Lychee.svg" height="100">

> [!IMPORTANT]  
> Lychee is currently in the early alpha stage of development.  
> There is no guarantee the engine will run.   


<img src="resource/screenshots/LycheeApp.png">

## Dependencies
- [glad](https://glad.dav1d.de/)
- [GLFW](https://github.com/glfw/glfw)
- [glm](https://github.com/g-truc/glm)
- [ImGui](https://github.com/ocornut/imgui)
- [EnTT](https://github.com/skypjack/entt)
- [spdlog](https://github.com/gabime/spdlog)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)


## Setup
### Requirements
- Cmake Version **Version 3.28** or higher
- **MSVC 19.39.33521.0** or higher

### Setup Repo
1. Clone
    ```bash 
    git clone git@github.com:FlexHaufen/Lychee.git
    ```

2. Setup submodules in ./Lychee
    ```shell
    git submodule update --init --recursive
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
            "program": "${workspaceFolder}/build/bin/release/LycheeApp.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "console": "internalConsole"
        },
        {
            "name": "Debug",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/bin/debug/LycheeApp.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "console": "internalConsole"
        }
    ]
}
```



## Acknowledgements
 - [Hazel Engine](https://github.com/TheCherno/Hazel)
 - [Game Engine Series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
 - [ImGui Theme by @Trippasch](https://github.com/Trippasch)