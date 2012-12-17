#ifndef GAMEPIECE_H
#define GAMEPIECE_H

class CPlayer;
class IGamePiece
{
public:
	IGamePiece(CPlayer* owner): m_owner(owner) { }

	inline CPlayer* GetOwner(void) const { return m_owner; }
	inline void SetOwner(CPlayer* owner) { m_owner = owner; }

	// Attempt to move this piece to the specified row and column.
	// @param row The row you want to place this piece.
	// @param col The column you want to place this piece.
	// \return True if the move was successful; false otherwise.
	virtual bool Move(size_t row, size_t col) = 0;

private:
	CPlayer* m_owner; // Player that owns this piece.
};

#endif