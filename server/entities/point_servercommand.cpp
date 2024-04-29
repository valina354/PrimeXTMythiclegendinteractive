/*
===== ent_cmd.cpp ========================================================
  goldsrc equiv of various source console command entities From Project Desolation
*/
#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "saverestore.h"
#include "gamerules.h"

//extern cvar_t	*sv_allow_point_servercommand;

//=====================================
// target_clientcommand - goldsrc emulation of "point_clientcommand"
//=====================================

//todo: what max size are we comfortable with?
#define MAX_ENT_CMD_SIZE 150
class CTargetClientCommand : public CPointEntity
{
public:
	void Spawn(void);
	void KeyValue(KeyValueData *pkvd);

	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	/* void Think( void );
	void Play( void ); */

	//void DoCommand( CBaseEntity *pTarget )

protected:
	char m_sCmd[MAX_ENT_CMD_SIZE];
};

void CTargetClientCommand::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "concommand"))
	{
		sprintf(m_sCmd, "%s\n", pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CPointEntity::KeyValue(pkvd);
}
LINK_ENTITY_TO_CLASS(target_clientcommand, CTargetClientCommand)
LINK_ENTITY_TO_CLASS(point_clientcommand, CTargetClientCommand)


void CTargetClientCommand::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!pActivator->IsPlayer())
		return; //not a player...don't do it!!

	//DoCommand(pActivator);
	CLIENT_COMMAND(pActivator->edict(), m_sCmd);

	UTIL_Remove(this);
}

void CTargetClientCommand::Spawn(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
}

//=====================================
// target_servercommand - goldsrc emulation of "point_servercommand"
//=====================================
class CTargetServerCommand : public CTargetClientCommand
{
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};
LINK_ENTITY_TO_CLASS(target_servercommand, CTargetServerCommand)
LINK_ENTITY_TO_CLASS(point_servercommand, CTargetServerCommand)

void CTargetServerCommand::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SERVER_COMMAND(m_sCmd);

	UTIL_Remove(this);
}