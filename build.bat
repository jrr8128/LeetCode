@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
  echo usage: build.bat path\to\solution.cpp
  exit /b 1
)

call "%ProgramFiles(x86)%\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul

set "MODE=%~2"
set "COMP=cl"
set "CFLAGS=/nologo /std:c++20 /W4 /EHsc"
if /I "%MODE%"=="cov" (
  set "COMP=clang-cl"
  set "CFLAGS=/nologo /std:c++20 /W4 /EHsc /Od /Zi /clang:-fprofile-instr-generate /clang:-fcoverage-mapping"
)

for %%I in ("%~1") do (
  set "SRC=%%~fI"
  set "DIR=%%~dpI"
  set "BASE=%%~nI"
)

set "ROOT=%~dp0"
set "CATCH_INC=%ROOT%third_party\catch2"
set "CATCH_CPP=%CATCH_INC%\catch_amalgamated.cpp"
set "CATCH_OBJ=%ROOT%build\catch_amalgamated.obj"

if not exist "%ROOT%build" mkdir "%ROOT%build"

%COMP% %CFLAGS% /c "%SRC%" /Fo:"%DIR%%BASE%.obj" /I"%CATCH_INC%"
if errorlevel 1 exit /b 1

if not exist "%CATCH_OBJ%" goto build_catch
for %%A in ("%CATCH_OBJ%") do set "OBJT=%%~tA"
for %%A in ("%CATCH_CPP%") do set "CPPT=%%~tA"
if "!CPPT!" GTR "!OBJT!" goto build_catch
goto link

:build_catch
%COMP% %CFLAGS% /c "%CATCH_CPP%" /Fo:"%CATCH_OBJ%" /I"%CATCH_INC%"
if errorlevel 1 exit /b 1

:link
%COMP% %CFLAGS% "%DIR%%BASE%.obj" "%CATCH_OBJ%" /Fe:"%DIR%%BASE%.exe"

if /I "%MODE%"=="cov" (
  set LLVM_PROFILE_FILE=%ROOT%default.profraw
  "%DIR%%BASE%.exe"
  llvm-profdata merge -sparse "%ROOT%default.profraw" -o "%ROOT%default.profdata"
  llvm-cov report "%DIR%%BASE%.exe" "-instr-profile=%ROOT%default.profdata" -ignore-filename-regex="third_party|catch_amalgamated" > "%DIR%coverage_report.txt"
)

if /I "%MODE%"=="ubsan" (
  set "COMP=clang-cl"
  set "CFLAGS=/nologo /std:c++20 /W4 /EHsc /Od /Zi /clang:-fsanitize=undefined /clang:-fno-sanitize-recover=undefined"
)
