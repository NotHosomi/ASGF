#include "include/ASGF/SoundGroup.h"

void SoundGroup::AddSounds(const std::string& sNamePrefix, int count)
{
	std::string name;
	for (int i = 0; i < count; ++i)
	{
		name = sNamePrefix + std::to_string(count);
		AddSound(sNamePrefix);
	}
}

void SoundGroup::AddSounds(std::vector<std::string> names)
{
	for (auto& name : names)
	{
		AddSound(name);
	}
}

void SoundGroup::AddSound(const std::string& name)
{
	m_vSounds.emplace_back(name);
}

void SoundGroup::Clear()
{
	m_vSounds.clear();
}

void SoundGroup::PlayRandom()
{
	Play(rand() % m_vSounds.size());
}

void SoundGroup::Play(int index)
{
	m_vSounds[index].Play();
}
