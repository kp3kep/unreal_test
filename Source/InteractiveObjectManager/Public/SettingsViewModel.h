#pragma once

#include "MyProjectSettings.h"
#include "UObject/Object.h"
#include "SettingsViewModel.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnTypeChanged, ESpawnObjectType, NewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnColorChanged, FLinearColor, NewColor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnScaleChanged, float, NewScale);


UCLASS(Blueprintable)
class INTERACTIVEOBJECTMANAGER_API USettingsViewModel : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SaveSettings() const;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetSpawnObjectColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetSpawnObjectScale(float InScale);
	
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetSelectedSpawnType(const FString& InString);

	void SetSpawnObjectType(ESpawnObjectType InType);

	UPROPERTY(BlueprintAssignable, Category = "Settings|Events")
	FOnSpawnTypeChanged OnSpawnTypeChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Settings|Events")
	FOnSpawnColorChanged OnSpawnColorChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Settings|Events")
	FOnSpawnScaleChanged OnSpawnScaleChanged;

protected:	
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	ESpawnObjectType SpawnObjectType = ESpawnObjectType::Cube;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	FLinearColor SpawnObjectColor = FLinearColor::White;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float SpawnObjectScale = 1.0f;;
};
