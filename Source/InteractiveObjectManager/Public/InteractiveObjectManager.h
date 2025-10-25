#pragma once

#include "Modules/ModuleManager.h"

class FInteractiveObjectManagerModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
