#pragma once

#include "../misc/CUserCmd.hpp"

#define MULTIPLAYER_BACKUP 150

class bf_write;
class bf_read;

class CInput
{
public:
	std::byte			pad0[0xC];				//0x0000
	bool				m_fTrackIRAvailable;	//0x000C
	bool				m_fMouseInitialized;	//0x000D
	bool				m_fMouseActive;			//0x000E
	std::byte			pad1[0xB2];				//0x000F
	bool				m_fCameraInThirdPerson;	//0x00C1
	std::byte			pad2[0x2];				//0x00C2
	Vector				m_vecCameraOffset;		//0x00C4
	std::byte			pad3[0x38];				//0x00D0
	CUserCmd* m_pCommands;						//0x0108
	CVerifiedUserCmd* m_pVerifiedCommands;		//0x010C

	CUserCmd* CInput::GetUserCmd(int sequence_number)
	{
		return &m_pCommands[sequence_number % MULTIPLAYER_BACKUP];
	}

	CVerifiedUserCmd* GetVerifiedUserCmd(int sequence_number)
	{
		return &m_pVerifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
	}
};