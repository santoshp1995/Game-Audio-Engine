#ifndef VOICE_MAN_H 
#define VOICE_MAN_H

#include "Manager.h"
#include "Voice.h"

class VoiceMan : public Manager
{
private:
	VoiceMan(int reserveNum = 3, int reserveGrow = 1);
	VoiceMan(const VoiceMan&) = delete;
	VoiceMan& operator = (const VoiceMan&) = delete;
	VoiceMan() = delete;
	~VoiceMan();

public:
	static void Create(int reserveNum, int reserveGrow);
	static void Destroy();
	static Voice* Add(VoiceID voice_id, WaveDataID wave_id);
	static Voice* Add(VoiceID voice_id, WaveDataID wave_id, IXAudio2VoiceCallback* pCallback);
	static Voice* Find(VoiceID voice_id);
	static void Remove(Voice* pVoice);
	static void Dump();

	


protected:
	// override abstract methods
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;


private:

	static VoiceMan* GetInstance();

	static VoiceMan* pInstance;
	Voice* pNodeCompare;
	


};



#endif 