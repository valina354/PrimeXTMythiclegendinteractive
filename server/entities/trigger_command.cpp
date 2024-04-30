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
#include <string>

class CTriggerCommand : public CBaseEntity {
public:
    DECLARE_CLASS(CTriggerCommand, CBaseEntity);

    CTriggerCommand() : netname("") {}

    void Spawn() override {
        CBaseEntity::Spawn();
        SetUse(&CTriggerCommand::Use);
    }

    void KeyValue(KeyValueData* pkvd) override {
        if (FStrEq(pkvd->szKeyName, "netname")) {
            netname = pkvd->szValue;
            pkvd->fHandled = true;
        } else {
            BaseClass::KeyValue(pkvd);
        }
    }

    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override {
        if (!netname.empty()) {
            SERVER_COMMAND(netname.c_str());
        }
    }

private:
    std::string netname;
};

LINK_ENTITY_TO_CLASS(trigger_command, CTriggerCommand);