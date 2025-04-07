@echo off
echo Compiling DirectNet Server for Windows...

g++ Server/Server.cpp -o Server.exe -lws2_32 -static -static-libgcc -static-libstdc++

if %ERRORLEVEL% neq 0 (
    echo Compilation failed.    
) else (
    echo Build successful! Output: Server.exe
)

echo Compiling DirectNet Client for Windows...

g++ Client/Client.cpp -o Client.exe -lws2_32 -static -static-libgcc -static-libstdc++

if %ERRORLEVEL% neq 0 (
    echo Compilation failed.    
) else (
    echo Build successful! Output: Client.exe
)
pause
