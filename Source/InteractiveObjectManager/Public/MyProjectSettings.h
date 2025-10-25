#pragma once

#include "GameFramework/GameUserSettings.h"
#include "MyProjectSettings.generated.h"

class AInteractiveObjectBase;

UENUM(BlueprintType)
enum class ESpawnObjectType : uint8
{
	Cube = 0 UMETA(DisplayName = "Cube"),
	Sphere = 1 UMETA(DisplayName = "Sphere"),
	MAX UMETA(Hidden)
};

/**
 * 
 */
UCLASS()
class INTERACTIVEOBJECTMANAGER_API UMyProjectSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	static UMyProjectSettings* Get();
	UClass* GetClassToSpawn(ESpawnObjectType SelectedSpawnObjectType) const;

	UPROPERTY(Config)
	ESpawnObjectType DefaultSpawnObjectType = ESpawnObjectType::Cube;

	UPROPERTY(Config)
	FLinearColor DefaultSpawnObjectColor = FLinearColor::White;

	UPROPERTY(Config)
	float DefaultSpawnObjectScale = 1.0f;

	UPROPERTY(Config) 
	TSoftClassPtr<AInteractiveObjectBase> CubeClassToSpawn;

	UPROPERTY(Config)
	TSoftClassPtr<AInteractiveObjectBase> SphereClassToSpawn;
};
