<div align="center">
  <br>
  <img src="resource/images/Lychee.svg" height="100">
  <h1>Lychee </h1>
  <strong>A simple, fast & lightweight voxel engine written in C++</strong>
  <br>
  <img src="https://ziadoua.github.io/m3-Markdown-Badges/badges/LicenceGPLv3/licencegplv31.svg" height="20" link="LICENCE">
</div>
<br>

> [!WARNING] 
> Lychee is currently in the early alpha stage of development.  
> There is no guarantee the engine will run.   

<div align="center">
<img src="https://img.shields.io/badge/VULKAN-A41E22?style=for-the-badge&logo=vulkan" alt="https://www.vulkan.org/">
<img src="https://img.shields.io/badge/CMake-1ea4a0?style=for-the-badge&logo=cmake" alt="https://cmake.org/">
<img src="https://img.shields.io/badge/C++-1ea4a0?style=for-the-badge&logo=cplusplus" alt="https://cmake.org/">
</div>

<br>
<br>

<div align="center">
    <h2> 🛠️ Setup </h2>
</div>

### 📋 Requirements
- [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)
- [CMake](https://cmake.org/)
- [MSVC](https://visualstudio.microsoft.com/de/vs/features/cplusplus/)

### ⚙️ Setup Repo
1. Clone
    ```bash 
    git clone git@github.com:FlexHaufen/Lychee.git
    ```

2. Setup submodules in ./Lychee
    ```bash
    git submodule update --init --recursive
    ```
    ImGui Has to be on docking branch

### 🏗️ Build
Using Visual Studio Code:
1. `F1` ➡️ `CMake: Configure`
2. `F1` ➡️ `CMake: Select Variant` ➡️ `Release`
3. `F1` ➡️ `CMake: Build`


### 🚀 Run
Run `LycheeApp.exe` in `/build/bin/release/`

<div align="center">
    <h2> 🫡 Acknowledgements </h2>
</div>

 - [Hazel Engine](https://github.com/TheCherno/Hazel)
 - [Vulkan Tutorial by @GetIntoGameDev](https://www.youtube.com/@GetIntoGameDev)
 - [Game Engine Series by @TheCherno](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
 - [ImGui Theme by @Trippasch](https://github.com/Trippasch)