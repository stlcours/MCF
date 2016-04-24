@echo off

set CompilerFlags=-Wall -Wextra -pipe -mfpmath=sse,387 -msse2 -mno-stack-arg-probe -mno-accumulate-outgoing-args -mpush-args -masm=intel
set LinkerFlags=-Wall -Wextra -static
set ExtraLibs=-lversion -lshlwapi

set CFlags=%CompilerFlags% -std=c11
set CPPFlags=%CompilerFlags% -std=c++14

if not "%1"=="Release" (
	set CompilerFlags=%CompilerFlags% -fno-builtin -g -O0
	set LinkerFlags=%LinkerFlags% -O0
) else (
	set CompilerFlags=%CompilerFlags% -DNDEBUG -O3 -flto -ffunction-sections -fdata-sections
	set LinkerFlags=%LinkerFlags% -O3 -flto -Wl,--gc-sections,-s
)

windres -i MCFBuild.rc -o "%temp%\MCFBuild.rc.o" -O coff
g++ %CPPFlags% *.cpp "%temp%\MCFBuild.rc.o" %LinkerFlags% %ExtraLibs%
