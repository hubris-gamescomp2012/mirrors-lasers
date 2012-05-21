#ifndef SELECT_LISTENER_HPP
#define SELECT_LISTENER_HPP

class GUIManager;
class Trader;
class GameInst;

class SelectListener
{
public:
	enum Type
	{
		INVALID_LISTENER = 0,
		LISTENER_TRADER,
		LISTENER_SETTLEMENT,
		LISTENER_COMPANY,
		LISTENER_SYSTEM,
		//
		MAX_LISTENER
	};
	SelectListener(GameInst& a_Owner);
	//
	void Fire(void* a_pCallee, SelectListener::Type a_MyType);
	//
private:
	GameInst& Owner;
	//
};

#endif	//SELECT_LISTENER_HPP