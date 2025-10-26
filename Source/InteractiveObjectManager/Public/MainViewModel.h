#pragma once

#include "InteractiveObjectManagerSubsystem.h"
#include "MyProjectSettings.h"
#include "UObject/Object.h"
#include "MainViewModel.generated.h"

class AInteractiveObjectBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnedObjectsChanged, const TArray<AInteractiveObjectBase*>&, NewObjects);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedObjectChanged, AInteractiveObjectBase*, NewSelection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedColorChanged, FLinearColor, NewColor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedScaleChanged, float, NewScale);

UCLASS(Blueprintable)
class INTERACTIVEOBJECTMANAGER_API UMainViewModel : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UInteractiveObjectManagerSubsystem* InSubsystem);

	UFUNCTION(BlueprintCallable, Category = "Main")
	void RequestSpawnObject() const;

	UFUNCTION(BlueprintCallable, Category = "Main")
	void RequestDeleteSelectedObject() const;
	
	UFUNCTION(BlueprintCallable, Category = "Main")
	void SetSelectedObjectFromUI(AInteractiveObjectBase* ObjectToSelect) const;

	UFUNCTION(BlueprintCallable, Category = "Main")
	void SetSelectedSpawnObjectType(const FString& NewType);

	UFUNCTION(BlueprintCallable, Category = "Main|Selection")
	void SetSelectedObjectColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable, Category = "Main|Selection")
	void SetSelectedObjectScale(float InScale);

	void UpdateSpawnedObjectsList(const TArray<AInteractiveObjectBase*>& UpdatedObjects);
	void UpdateSelectedObject(AInteractiveObjectBase* NewSelectedObject);

	UFUNCTION(BlueprintPure, Category="Main")
	const TArray<AInteractiveObjectBase*>& GetSpawnedObjects() const { return SpawnedObjects; }

	UFUNCTION(BlueprintPure, Category="Main")
	AInteractiveObjectBase* GetSelectedObject() const { return SelectedObject; }

	UFUNCTION(BlueprintPure, Category="Main|Selection")
	FLinearColor GetSelectedObjectColor() const { return SelectedObjectColor; }

	UFUNCTION(BlueprintPure, Category="Main|Selection")
	float GetSelectedObjectScale() const { return SelectedObjectScale; }

	UPROPERTY(BlueprintAssignable, Category = "Main|Events")
	FOnSpawnedObjectsChanged OnSpawnedObjectsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Main|Events")
	FOnSelectedObjectChanged OnSelectedObjectChanged;

	UPROPERTY(BlueprintAssignable, Category = "Main|Events")
	FOnSelectedColorChanged OnSelectedColorChanged;

	UPROPERTY(BlueprintAssignable, Category = "Main|Events")
	FOnSelectedScaleChanged OnSelectedScaleChanged;

protected:
	UPROPERTY(BlueprintReadOnly, Category="Main")
	TArray<AInteractiveObjectBase*> SpawnedObjects;

	UPROPERTY(BlueprintReadWrite, Category="Main")
	AInteractiveObjectBase* SelectedObject;

	UPROPERTY(BlueprintReadOnly, Category="Main", meta=(AllowPrivateAccess="true"))
	ESpawnObjectType SelectedSpawnObjectType;

	UPROPERTY(BlueprintReadWrite, Category="Main|Selection", meta=(AllowPrivateAccess="true"))
	FLinearColor SelectedObjectColor = FLinearColor::Black;

	UPROPERTY(BlueprintReadWrite, Category="Main|Selection", meta=(AllowPrivateAccess="true"))
	float SelectedObjectScale = 0.0f;

private:
	UPROPERTY()
	TObjectPtr<UInteractiveObjectManagerSubsystem> ManagerSubsystem;
};
