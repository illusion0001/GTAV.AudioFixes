# GTAV.AudioFixes

An .asi mod that fixes audio-related stutters and optionally removes the 188 FPS limit imposed by the audio engine.

## Description

This mod applies two changes to RAGE's audio engine to improve the experience of GTA V on modern hardware.
1. When your FPS goes above ~140, or occasionally when using the pause menu, the game will experience stutters. This is due to the audioTimeout functionality of RAGE that ensures synchronisation between the audio and main threads. The mod disables that synchronisation which removes the stutters without any impact on gameplay. 
2. RAGE has an internal setting called "audio frame limiter" that effectively limits your FPS to 188. This mod disables that setting, allowing you to achieve higher FPS. Disabling this setting does have some impact on gameplay, such as making it harder to delay dialogue by spamming your character's special ability. You will also hit another FPS limit at 270 FPS during normal gameplay, this is imposed by a mission script and not removed in this mod.

The mod is distrubuted in two versions 
- `GTAV.StutterFix.asi` only fixes the high-fps/menu stutters, while leaving the 188 FPS limit. 
- `GTAV.UncapFPS.asi` both fixes the stutters and removes the 188 FPS limit

## Getting Started

### Dependencies

* ScriptHookV from Alexander Blade http://www.dev-c.com/gtav/scripthookv/

### Installing

* Download `GTAV.StutterFix.asi` or `GTAV.UncapFPS.asi` from the Releases page
* Add the downloaded asi to your game folder
* Ensure the BattlEye anti-cheat is disabled in your game's retailer (Rockstar Games Launcher/Epic Games Store/Steam). 

## Acknowledgments
Special thanks to the nta and the CitizenFX/FiveM project for researching these issues and implementing fixes for them in FiveM. This mod wouldn't be possible without their work <3
Code that is adapted from the CitizenFX project is marked with a comment `/* Adapted from the CitizenFX project` and licensed according to the [LICENSE.CitizenFX](LICENSE.CitizenFX) file.
* [FiveM](https://github.com/citizenfx/fivem)
