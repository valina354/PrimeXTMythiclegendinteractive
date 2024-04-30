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
#include "cbase.h"
#include "triggers.h"

class CTriggerAutosave : public CBaseTrigger {
public:
    void Spawn() override;
    void Touch(CBaseEntity* pOther) override;
};

void CTriggerAutosave::Spawn() {
    InitTrigger();
    CBaseTrigger::Spawn();
    SetTouch(&CTriggerAutosave::Touch);
}

void CTriggerAutosave::Touch(CBaseEntity* pOther) {
    if (!pOther->IsPlayer()) {
        return;
    }

    SERVER_COMMAND("save autosave\n");
    UTIL_Remove(this);
}

LINK_ENTITY_TO_CLASS(trigger_autosave, CTriggerAutosave);
