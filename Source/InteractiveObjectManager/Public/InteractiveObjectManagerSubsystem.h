#pragma once

#include "InteractiveObjectBase.h"
#include "InteractiveObjectSettings.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractiveObjectManagerSubsystem.generated.h"

class UMainViewModel;
class USettingsViewModel;

UCLASS()
class INTERACTIVEOBJECTMANAGER_API UInteractiveObjectManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void SpawnObjectInWorld(ESpawnObjectType SelectedSpawnObjectType);
	void DeleteSelectedObject();
	
	UFUNCTION(BlueprintPure, Category = "Manager")
	UMainViewModel* GetMainViewModel() const { return MainViewModel; }
	
	UFUNCTION(BlueprintPure, Category = "Manager")
	USettingsViewModel* GetSettingsViewModel() const { return SettingsViewModel; }

	void SetSelectedObject(AInteractiveObjectBase* NewSelection);
	void UpdateSelectedActorColor(const FLinearColor& InColor) const;
	void UpdateSelectedActorScale(float InScale) const;

private:
	AInteractiveObjectBase* SpawnActor(UClass* ClassToSpawn) const;

protected:
	UPROPERTY(Transient)
	TObjectPtr<UMainViewModel> MainViewModel;

	UPROPERTY(Transient)
	TObjectPtr<USettingsViewModel> SettingsViewModel;
	
	UPROPERTY(Transient)
	TArray<AInteractiveObjectBase*> SpawnedObjectsList;

	UPROPERTY(Transient)
	TObjectPtr<AInteractiveObjectBase> CurrentSelectedObject;
};
