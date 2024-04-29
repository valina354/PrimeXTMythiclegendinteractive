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

#include "triggers.h"

// Define the CTriggerHurt class
class CTriggerHurt : public CBaseTrigger {
public:
    DECLARE_CLASS(CTriggerHurt, CBaseTrigger);


    CTriggerHurt() : damageAmount(10.0f), damageType(DMG_GENERIC), damageInterval(1.0f), lastDamageTime(0) {
    }

    void Spawn() override {
        InitTrigger();
        CBaseTrigger::Spawn();
        SetTouch(&CTriggerHurt::Touch);
    }

    // Touch function
    void Touch(CBaseEntity* pOther) override {
        if (!pOther || !pOther->IsPlayer()) {
            return;
        }

        float currentTime = gpGlobals->time;
        if (currentTime - lastDamageTime >= damageInterval) {
            pOther->TakeDamage(VARS(edict()), VARS(edict()), damageAmount, damageType);
            lastDamageTime = currentTime;
        }
    }

    // Load properties from key-value pairs
    void KeyValue(KeyValueData* pkvd) override {
        if (FStrEq(pkvd->szKeyName, "damage")) {
            damageAmount = atof(pkvd->szValue);
        }
        else if (FStrEq(pkvd->szKeyName, "damage_type")) {
            damageType = atoi(pkvd->szValue);
        }
        else if (FStrEq(pkvd->szKeyName, "interval")) {
            damageInterval = atof(pkvd->szValue);
        }
        else {
            BaseClass::KeyValue(pkvd);
        }
    }

private:
    float damageAmount;
    int damageType;
    float damageInterval;
    float lastDamageTime;
};

LINK_ENTITY_TO_CLASS(trigger_hurt, CTriggerHurt);
