#include "include\ASGF\Sound.h"
#include <assert.h>
#include <iostream>
#include <SDL.h>

Uint16 Sound::audioFormat{};
int Sound::audioFrequency{};
int Sound::audioChannelCount{};

void Sound::Setup()
{
	Mix_QuerySpec(&audioFrequency, &audioFormat, &audioChannelCount);
}

Sound::Sound(const std::string sName)
{
	SetSound(sName);
}

void Sound::SetSound(const std::string sName)
{
	T_ChunkInfo* pChunkInfo = Sound::Lookup(sName);
	if (pChunkInfo == nullptr)
	{
		Load(sName);
		pChunkInfo = Sound::Lookup(sName);
		assert(pChunkInfo != nullptr && "Texture should DEFINITELY exist after a load call");
	}
	Mount(sName, pChunkInfo);
}

void Sound::Play()
{
	m_nCurrentChannel = Mix_PlayChannel(-1, m_pChunkInfo->pChunk, 0);
}

void Sound::PlayLooping(int nLoops)
{
	m_nCurrentChannel = Mix_PlayChannel(-1, m_pChunkInfo->pChunk, nLoops);
}

void Sound::Stop()
{
	Mix_HaltChannel(m_nCurrentChannel);
	m_nCurrentChannel = -1;
}

int Sound::GetDuration()
{
	return m_pChunkInfo->nDurationMils;
}

Sound::T_ChunkInfo* Sound::Lookup(const std::string& sName)
{
	auto iter = ms_mChunkCache.find(sName);
	if (iter == ms_mChunkCache.end())
		return nullptr;
	return &iter->second;
}

bool Sound::Load(const std::string& sName)
{
	static std::string sDirPrefix = "Assets/Sounds/";
	std::string sFileAddr = sDirPrefix + sName;
	
	// file info
	Mix_Chunk* chunk = Mix_LoadWAV(sFileAddr.c_str());
	if (chunk == nullptr)
	{
		std::cout << "SDL Error - Failed to load " << sName << "\t" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Failed to load sound", ("Failed to load " + sName + " - SDL Error:" + SDL_GetError()).c_str(), nullptr);
		SDL_ClearError();
		return false;
	}
	T_ChunkInfo tInfo;
	tInfo.pChunk = chunk;
	tInfo.nDurationMils = ((chunk->alen / ((audioFormat & 0xFF) / 8) / audioChannelCount * 1000) / audioFrequency) / 1000.0f;
	ms_mChunkCache.insert({ sName, tInfo });
	return true;
}

void Sound::Mount(const std::string& sName, T_ChunkInfo* pChunkInfo)
{
	m_sChunkName = sName;
	m_pChunkInfo = pChunkInfo;
}

void Sound::FreeCache()
{
	for (auto& iter : ms_mChunkCache)
	{
		Mix_FreeChunk(iter.second.pChunk);
	}
	ms_mChunkCache.clear();
}

void Sound::RemoveFromCache(const std::string& sName)
{
	auto pIter = ms_mChunkCache.find(sName);
	if (pIter == ms_mChunkCache.end()) { return; }
	Mix_FreeChunk(pIter->second.pChunk);
	ms_mChunkCache.erase(sName);
}

int Sound::PlaySound(const std::string& sName)
{
	T_ChunkInfo* pChunkInfo = Sound::Lookup(sName);
	if (pChunkInfo == nullptr)
	{
		Load(sName);
		pChunkInfo = Sound::Lookup(sName);
		assert(pChunkInfo->pChunk != nullptr && "Sound should DEFINITELY exist after a load call");
	}
	return Mix_PlayChannel(-1, pChunkInfo->pChunk, 0);
}