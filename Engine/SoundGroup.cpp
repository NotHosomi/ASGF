#include "include/ASGF/SoundGroup.h"
#include "include/ASGF/DeferredCall.h"

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

void SoundGroup::PlayAllSequential()
{
	m_nSequenceIndex = 0;
	Play(0);
	ASGF::DeferCall([this]() {this->PlayNextInSequence(); }, m_vSounds[m_nSequenceIndex].GetDuration());
}

void SoundGroup::PlayNext()
{
	m_nSequenceIndex = (m_nSequenceIndex + 1) % m_vSounds.size();
	Play(m_nSequenceIndex);
}

void SoundGroup::Play(int index)
{
	m_nSequenceIndex = index;
	m_vSounds[index].Play();
}

void SoundGroup::PlayNextInSequence()
{
	Play(m_nSequenceIndex);
	if (m_nSequenceIndex < m_vSounds.size() - 1)
	{
		ASGF::DeferCall([this]() {this->PlayNextInSequence(); }, m_vSounds[m_nSequenceIndex].GetDuration());
	}
}
