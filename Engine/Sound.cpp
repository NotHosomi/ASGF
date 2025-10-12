#include "include\ASGF\Sound.h"
#include <assert.h>
#include <iostream>
#include <SDL.h>

Sound::Sound(const std::string sName)
{
	SetSound(sName);
}

void Sound::SetSound(const std::string sName)
{
	Mix_Chunk* pChunk = Sound::Lookup(sName);
	if (pChunk == nullptr)
	{
		Load(sName);
		pChunk = Sound::Lookup(sName);
		assert(pChunk != nullptr && "Texture should DEFINITELY exist after a load call");
	}
	Mount(sName, pChunk);
}

void Sound::Play()
{
	m_nCurrentChannel = Mix_PlayChannel(-1, m_pChunk, 0);
}

void Sound::PlayLooping(int nLoops)
{
	m_nCurrentChannel = Mix_PlayChannel(-1, m_pChunk, nLoops);
}

void Sound::Stop()
{
	Mix_HaltChannel(m_nCurrentChannel);
	m_nCurrentChannel = -1;
}

Mix_Chunk* Sound::Lookup(const std::string& sName)
{
	auto iter = ms_mChunkCache.find(sName);
	if (iter == ms_mChunkCache.end())
		return nullptr;
	return iter->second;
}

bool Sound::Load(const std::string& sName)
{
	static std::string sDirPrefix = "Assets/Sounds/";
	std::string sFileAddr = sDirPrefix + sName;
	Mix_Chunk* chunk = Mix_LoadWAV(sFileAddr.c_str());
	if (chunk == nullptr)
	{
		std::cout << "SDL Error - Failed to load " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to load sound", ("Failed to load " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		SDL_ClearError();
		return false;
	}
	ms_mChunkCache.insert({ sName, chunk });
	return true;
}

void Sound::Mount(const std::string& sName, Mix_Chunk* pChunk)
{
	m_sChunkName = sName;
	m_pChunk = pChunk;
}

void Sound::FreeCache()
{
	for (auto& iter : ms_mChunkCache)
	{
		Mix_FreeChunk(iter.second);
	}
	ms_mChunkCache.clear();
}

void Sound::RemoveFromCache(const std::string& sName)
{
	auto pIter = ms_mChunkCache.find(sName);
	if (pIter == ms_mChunkCache.end()) { return; }
	Mix_FreeChunk(pIter->second);
	ms_mChunkCache.erase(sName);
}

int Sound::PlaySound(const std::string& sName)
{
	Mix_Chunk* pChunk = Sound::Lookup(sName);
	if (pChunk == nullptr)
	{
		Load(sName);
		pChunk = Sound::Lookup(sName);
		assert(pChunk != nullptr && "Sound should DEFINITELY exist after a load call");
	}
	return Mix_PlayChannel(-1, pChunk, 0);
}
