/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

#include <base/vmath.h>

class CCollision
{
	struct CTile *m_pTiles;
	struct CTile *m_pMaterial;
	struct CTile *m_pWater;
	int m_Width;
	int m_Height;
	class CLayers *m_pLayers;
	//class CGameClient* m_pWater;

	bool IsTile(int x, int y, int Flag=COLFLAG_SOLID) const;
	int GetTile(int x, int y) const;

public:
	enum
	{
		COLFLAG_SOLID=1,
		COLFLAG_DEATH=2,
		COLFLAG_NOHOOK=4,
	};

	CCollision();
	void Init(class CLayers *pLayers);
	bool CheckPoint(float x, float y, int Flag=COLFLAG_SOLID) const { return IsTile(round_to_int(x), round_to_int(y), Flag); }
	bool CheckPoint(vec2 Pos, int Flag=COLFLAG_SOLID) const { return CheckPoint(Pos.x, Pos.y, Flag); }
	int GetCollisionAt(float x, float y) const { return GetTile(round_to_int(x), round_to_int(y)); }
	int GetWaterCollisionAt(float x, float y, int Flag) const { return IsTile(round_to_int(x), round_to_int(y), Flag); }
	int GetMaterial(float x, float y, int Flag=COLFLAG_SOLID) const;
	int GetWater(float x, float y) const;
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

	bool IntersectWater(vec2 Pos0, vec2 Pos1, vec2* Position, vec2 Size);

	int IntersectLine(vec2 Pos0, vec2 Pos1, vec2 *pOutCollision, vec2 *pOutBeforeCollision) const;
	int IntersectLineWithWater(vec2 Pos0, vec2 Pos1, vec2* pOutCollision, vec2* pOutBeforeCollision, int Flag) const;
	void MovePoint(vec2 *pInoutPos, vec2 *pInoutVel, float Elasticity, int *pBounces) const;
	void Diffract(vec2* pInoutPos, vec2* pInoutVel, float Elasticity, int* pBounces, int Flag) const;
	void MoveBox(vec2 *pInoutPos, vec2 *pInoutVel, vec2 Size, float Elasticity, bool *pDeath=0) const;
	void MoveWaterBox(vec2* pInoutPos, vec2* pInoutVel, vec2 Size, float Elasticity, bool* pDeath = 0, float Severity = 0.95) const;
	bool TestBox(vec2 Pos, vec2 Size, int Flag=COLFLAG_SOLID) const;
	bool TestBoxWater(vec2 Pos, vec2 Size) const;
};

#endif
