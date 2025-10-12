#pragma once
#include <string>
#include <unordered_map>
#include <SDL_mixer.h>

struct T_SoundInfo
{

};
class Sound
{
public:
	Sound() = default;
	Sound(const std::string sName);
	void SetSound(const std::string sName);

	void Play();
	void PlayLooping(int loops = -1);
	void Stop();

	// removed unused textures from cache
	//static void CleanupCache();
	// removes all textures from cache
	static void FreeCache();
	// removes specific key-value from cache
	static void RemoveFromCache(const std::string& sName);

	// plays a sound, and returns the channel index
	static int PlaySound(const std::string& sName);
private:
	int m_nCurrentChannel = -1;

	static Mix_Chunk* Lookup(const std::string& sName);
	static bool Load(const std::string& sName);
	void Mount(const std::string& sName, Mix_Chunk* pChunk);

	std::string m_sChunkName = "";
	Mix_Chunk* m_pChunk = nullptr;

	inline static std::unordered_map<std::string, Mix_Chunk*> ms_mChunkCache;
};