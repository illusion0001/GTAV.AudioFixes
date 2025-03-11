#include "script.h"
#include "utils.h"

/// <summary>
/// The audioTimeout field controls something related to the synchronization of the game thread and the audio thread. 
/// This occassionally causes stutters at high FPS or when the game is paused. Setting it to 0 bypasses this synchronization check
/// and fixes the stutters.
/// </summary>
bool enableStutterFix = true;

/// <summary>
/// The game is capped to 188FPS by the audio engine because of an engine setting called rage::g_audUseFrameLimiter.
/// Disabling this audio frame limiter uncaps the FPS of the game up to another limit of 270fps, imposed by CSystem::EndFrame.
/// As of version 1.1 we also remove that frame limiter to truly unlock the fps.
/// </summary>
bool uncapFPS = true;

void _main()
{
	static bool useSynchronousAudio = true;
	static bool lastUseSynchronousAudio = false;

	HMODULE game = GetModuleHandleW(L"GTA5_Enhanced.exe");
	if (!game)
	{
		return;
	}
	uintptr_t base = (uintptr_t)game;

	/*
	*	Adapted from the CitizenFX project, retrieved 2022-12-04.
	*   You can view the original project and license terms at:
	*	https://runtime.fivem.net/fivem-service-agreement-4.pdf
	*	https://github.com/citizenfx/fivem/blob/master/code/LICENSE
	*/
	const char* asynchronousAudioPattern = "48 89 d9 89 fa e8 ? ? ? ? 80 3d ? ? ? ? 00 75 ? e8 ? ? ? ?";
	const char* audioTimeoutPattern = "81 c3 e8 03 00 00 39 d7 0f 94 c1 39 d8";

	/*
	*   Credit to Special For for finding this CSystem frame limiter sleep loop and 
	*/
	//const char* frameLimiterPattern = "F3 44 0F 59 05 ? ? ? ? 0F 28 C7 F3 41 0F 58 C0 0F 2F C6 72 ? E8";
	const char* audioLimiter2Pattern = "48 8b 0d ? ? ? ? ba ff ff ff ff e8 ? ? ? ? 0f b6";

	bool* asynchronousAudio = get_address<bool*>((uintptr_t)PatternScan(game, asynchronousAudioPattern) + 13);
	uint8_t* audioTimeout = (PatternScan(game, audioTimeoutPattern) + 2);
	if (enableStutterFix && audioTimeout)
	{
		int timeout = 0;
		Write(audioTimeout, &timeout, sizeof(timeout));
	}

	//uint8_t* frameLimiterLoop = (uint8_t*)(PatternScan(game, frameLimiterPattern));
	uint8_t* audioLimiter2 = (uint8_t*)(PatternScan(game, audioLimiter2Pattern));
	if (uncapFPS) {
		*asynchronousAudio = false;

		// If you load a save, these will be null because we have already patched that code and the pattern doesn't match
		if (audioLimiter2) {
			//nop(frameLimiterLoop + 20, 2);
			nop(audioLimiter2 + 12, 5);
		}
	}
}

void ScriptMain()
{
	_main();
}
