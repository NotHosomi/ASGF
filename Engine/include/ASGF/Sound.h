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
	static void Setup();

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
	static Uint16 audioFormat;
	static int audioFrequency;
	static int audioChannelCount;

	int m_nCurrentChannel = -1;

	struct T_ChunkInfo
	{
		Mix_Chunk* pChunk;
		float fDuration;
	};

	static T_ChunkInfo* Lookup(const std::string& sName);
	static bool Load(const std::string& sName);
	void Mount(const std::string& sName, T_ChunkInfo* pChunkInfo);

	std::string m_sChunkName = "";
	T_ChunkInfo* m_pChunkInfo = nullptr;

	inline static std::unordered_map<std::string, T_ChunkInfo> ms_mChunkCache;
};