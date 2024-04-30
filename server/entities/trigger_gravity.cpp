/*
 * Copyright (C) 2024 Jdjd Gaming
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/
#include "extdll.h"
#include "util.h"
#include "triggers.h"

class CTriggerGravity : public CBaseTrigger
{
    DECLARE_CLASS(CTriggerGravity, CBaseTrigger);
public:
    CTriggerGravity() : m_flGravity(1.0f) {}

    void Spawn() override;
    void Touch(CBaseEntity* pOther) override;
    void KeyValue(KeyValueData* pkvd) override;

private:
    float m_flGravity;
};


void CTriggerGravity::Spawn()
{
    CBaseTrigger::Spawn();
    InitTrigger();
    SetTouch(&CTriggerGravity::Touch);
}

void CTriggerGravity::KeyValue(KeyValueData* pkvd)
{
    if (FStrEq(pkvd->szKeyName, "gravity"))
    {
        m_flGravity = atof(pkvd->szValue);
        pkvd->fHandled = true;
    }
    else
    {
        BaseClass::KeyValue(pkvd);
    }
}

void CTriggerGravity::Touch(CBaseEntity* pOther)
{
    if (!pOther->IsPlayer())
    {
        return;
    }
    pOther->pev->gravity = m_flGravity;
}

LINK_ENTITY_TO_CLASS(trigger_gravity, CTriggerGravity);