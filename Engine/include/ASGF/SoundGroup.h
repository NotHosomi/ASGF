#pragma once
#include <vector>
#include <string>
#include "Sound.h"

class SoundGroup
{
public:
	SoundGroup() = default;
	void AddSounds(const std::string& sNamePrefix, const std::string& sFileExtension, int count);
	void AddSounds(std::vector<std::string> names);
	void AddSound(const std::string& name);
	void Clear();

	void PlayRandom();
	void PlayAllSequential();
	void PlayNext();
	void Play(int index);
protected:
	std::vector<Sound> m_vSounds;
	int m_nSequenceIndex;
	void PlayNextInSequence();
};

