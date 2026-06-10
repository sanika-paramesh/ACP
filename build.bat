@echo off
echo Building 2D Graphics Editor...

:: Check if gcc is available
where gcc >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo Compiling with gcc...
    gcc -Wall -Wextra -std=c99 src/main.c src/shapes.c -o editor.exe
    goto check_result
)

:: Check standard MSYS2 installations
if exist "C:\msys68\ucrt64\bin\gcc.exe" (
    echo Found GCC in C:\msys68\ucrt64\bin. Setting PATH...
    set "PATH=C:\msys68\ucrt64\bin;%PATH%"
    gcc -Wall -Wextra -std=c99 src/main.c src/shapes.c -o editor.exe
    goto check_result
)
if exist "C:\msys64\ucrt64\bin\gcc.exe" (
    echo Found GCC in C:\msys64\ucrt64\bin. Setting PATH...
    set "PATH=C:\msys64\ucrt64\bin;%PATH%"
    gcc -Wall -Wextra -std=c99 src/main.c src/shapes.c -o editor.exe
    goto check_result
)

:: Check if clang is available
where clang >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo Compiling with clang...
    clang -Wall -Wextra -std=c99 src/main.c src/shapes.c -o editor.exe
    goto check_result
)

:: Check if cl (MSVC) is available
where cl >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo Compiling with cl (MSVC)...
    cl /W4 /std:c11 src/main.c src/shapes.c /Fe:editor.exe
    goto check_result
)

echo ERROR: No C compiler (gcc, clang, cl) found in PATH.
echo Please install GCC (via MSYS64/MinGW) or Visual Studio MSVC, add it to your PATH, and try again.
exit /b 1

:check_result
if %ERRORLEVEL% equ 0 (
    echo Build successful! Run editor.exe to start.
    exit /b 0
) else (
    echo Build failed with error code %ERRORLEVEL%.
    exit /b %ERRORLEVEL%
)
