#include "triggers.h"

/**
*	@brief Kills anything that touches it without gibbing it
*/
class CTriggerKillNoGib : public CBaseTrigger
{
public:
	void Spawn() override;

	void KillTouch(CBaseEntity* pOther);
};

LINK_ENTITY_TO_CLASS(trigger_kill_nogib, CTriggerKillNoGib);

void CTriggerKillNoGib::Spawn()
{
	InitTrigger();

	SetTouch(&CTriggerKillNoGib::KillTouch);
	SetUse(nullptr);

	//TODO: this needs to be removed in order to function
	pev->solid = SOLID_NOT;
}

void CTriggerKillNoGib::KillTouch(CBaseEntity* pOther)
{
	if (pOther->pev->takedamage != DAMAGE_NO)
		pOther->TakeDamage(pev, pOther->pev, 500000, DMG_NEVERGIB);
}