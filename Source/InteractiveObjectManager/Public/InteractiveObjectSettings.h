#pragma once

#include "InteractiveObjectBase.h"
#include "Engine/DeveloperSettings.h"
#include "InteractiveObjectSettings.generated.h"

enum class ESpawnObjectType : uint8;

UCLASS(Config=InteractiveObjectManager, DefaultConfig, meta=(DisplayName="Interactive Object Settings"))
class INTERACTIVEOBJECTMANAGER_API UInteractiveObjectSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UClass* GetClassToSpawn(ESpawnObjectType SelectedSpawnObjectType) const;

protected:
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowAbstract = "False"))
	TSoftClassPtr<AInteractiveObjectBase> CubeClassToSpawn;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowAbstract = "False"))
	TSoftClassPtr<AInteractiveObjectBase> SphereClassToSpawn;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowAbstract = "False"))
	TSoftClassPtr<AInteractiveObjectBase> CylinderClassToSpawn;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowAbstract = "False"))
	TSoftClassPtr<AInteractiveObjectBase> ConeToSpawn;
};