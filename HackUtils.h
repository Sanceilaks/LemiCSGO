#pragma once
#include "vector.h"
#include "HackCore.h"
#include "VMatrix.h"
#include "CBaseEntity.h"
#include "defs.h"

namespace HacksF
{
	namespace HMath
	{
		static bool WorldToScreen(Math::CVector in, Math::CVector& out)
		{
			const Math::VMatrix w2sm = HackCore::GetInstance()->EngineClient->WorldToScreenMatrix();
			float w = w2sm[3][0] * in.x + w2sm[3][1] * in.y + w2sm[3][2] * in.z + w2sm[3][3];

			if (w > 0.001f)
			{
				int width, height; HackCore::GetInstance()->EngineClient->GetScreenSize(width, height);

				float fl1DBw = 1 / w;
				out.x = (width / 2) + (0.5f * ((w2sm[0][0] * in.x + w2sm[0][1] * in.y + w2sm[0][2] * in.z + w2sm[0][3]) * fl1DBw) * width + 0.5f);
				out.y = (height / 2) - (0.5f * ((w2sm[1][0] * in.x + w2sm[1][1] * in.y + w2sm[1][2] * in.z + w2sm[1][3]) * fl1DBw) * height + 0.5f);
				return true;
			}
			return false;
		}
	};
	namespace HGame
	{
		static Math::CVector GetEntityBone(CBaseEntity* pEntity, ECSPlayerBones Bone) 
		{
			Math::matrix3x4_t boneMatrix[128];

			if (!pEntity->setup_bones(boneMatrix, 128, 0x00000100, HackCore::GetInstance()->EngineClient->GetLastTimeStamp()))
				return Math::CVector();

			Math::matrix3x4_t hitbox = boneMatrix[Bone];

			return Math::CVector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
		}
	};
}