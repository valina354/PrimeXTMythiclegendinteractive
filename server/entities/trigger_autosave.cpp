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
