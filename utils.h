/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
*/

#pragma once

#include <string>
#include <windows.h>

// returns module load path with trailing slash
std::string GetCurrentModulePath();

std::uint8_t* PatternScan(void* module, const char* signature);

/*
* Adapted from the CitizenFX project, retrieved 2022-12-04
* You can view the original project and license terms at:
https://github.com/citizenfx/fivem/blob/master/code/LICENSE
https://runtime.fivem.net/fivem-service-agreement-4.pdf
*/
template<typename T>
inline T get_address(uintptr_t address)
{
	intptr_t target = *(int32_t*)(address);
	target += (address + 4);

	return (T)target;
}

template<typename AddressType>
inline void nop(AddressType address, size_t length)
{
	DWORD oldProtect;
	VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);

	memset((void*)address, 0x90, length);

	VirtualProtect((void*)address, length, oldProtect, &oldProtect);
}

template<typename AddressType>
inline void Write(AddressType address, const void* data, size_t length)
{
	DWORD oldProtect;
	VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);

	memcpy((void*)address, data, length);

	VirtualProtect((void*)address, length, oldProtect, &oldProtect);
}