@echo off
setlocal

REM Check if the user has provided a shader name
if "%~1"=="" (
    echo Usage: compile.bat nameOfShader
    exit /b 1
)

REM Set the shader name
set SHADER_NAME=%1

REM Set the Vulkan SDK path (adjust the version number as needed)
set VULKAN_SDK=%VK_SDK_PATH%

REM Check if the Vulkan SDK path exists
if not exist "%VULKAN_SDK%" (
    echo Vulkan SDK not found at %VULKAN_SDK%
    exit /b 1
)

REM Set the path to glslc
set GLSLC=%VULKAN_SDK%\Bin\glslc.exe

REM Compile the vertex shader
if exist "%SHADER_NAME%.vert" (
    "%GLSLC%" "%SHADER_NAME%.vert" -o "%SHADER_NAME%.vert.spv"
    if errorlevel 1 (
        echo Failed to compile vertex shader %SHADER_NAME.vert
        exit /b 1
    )
    echo Compilation complete.
) else (
    echo Vertex shader %SHADER_NAME.vert not found
)

REM Compile the fragment shader
if exist "%SHADER_NAME%.frag" (
    "%GLSLC%" "%SHADER_NAME%.frag" -o "%SHADER_NAME%.frag.spv"
    if errorlevel 1 (
        echo Failed to compile fragment shader %SHADER_NAME.frag
        exit /b 1
    )
    echo Compilation complete.
) else (
    echo Fragment shader %SHADER_NAME.frag not found
)

endlocal