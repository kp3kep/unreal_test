#pragma once

#include "GameFramework/GameUserSettings.h"
#include "MyProjectSettings.generated.h"

UENUM(BlueprintType)
enum class ESpawnObjectType : uint8
{
	Cube = 0 UMETA(DisplayName = "Cube"),
	Sphere = 1 UMETA(DisplayName = "Sphere"),
	Cylinder = 2 UMETA(DisplayName = "Cylinder"),
	Cone = 3 UMETA(DisplayName = "Cone"),
	
	MAX UMETA(Hidden)
};

UCLASS()
class INTERACTIVEOBJECTMANAGER_API UMyProjectSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	static UMyProjectSettings* Get();

	UPROPERTY(Config)
	ESpawnObjectType DefaultSpawnObjectType = ESpawnObjectType::Cube;

	UPROPERTY(Config)
	FLinearColor DefaultSpawnObjectColor = FLinearColor::White;

	UPROPERTY(Config)
	float DefaultSpawnObjectScale = 1.0f;
};
