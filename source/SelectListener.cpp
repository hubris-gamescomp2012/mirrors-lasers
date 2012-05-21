#include "SelectListener.hpp"
#include "GameInst.hpp"

SelectListener::SelectListener(GameInst& a_Owner)
:	Owner(a_Owner)
{
	//
}

void SelectListener::Fire(void* a_pCallee, SelectListener::Type a_MyType)	//yay for void pointers
{
	Owner.Select(a_pCallee, a_MyType);
}
