#include "MainViewModel.h"
#include "InteractiveObjectManagerSubsystem.h"

void UMainViewModel::Initialize(UInteractiveObjectManagerSubsystem* InSubsystem, USettingsViewModel* InSettingsVM)
{
	ManagerSubsystem = InSubsystem;
}

void UMainViewModel::RequestSpawnObject() const
{
	if (ManagerSubsystem)
	{
		ManagerSubsystem->SpawnObjectInWorld(SelectedSpawnObjectType);
	}
}

void UMainViewModel::SetSelectedObjectFromUI(AInteractiveObjectBase* ObjectToSelect) const
{
	if (ManagerSubsystem)
	{
		ManagerSubsystem->SetSelectedObject(ObjectToSelect);
	}
}

void UMainViewModel::SetSelectedSpawnObjectType(const FString& NewType)
{
	int32 Index = StaticEnum<ESpawnObjectType>()->GetIndexByNameString(NewType);
	SelectedSpawnObjectType = StaticCast<ESpawnObjectType>(Index);
}

void UMainViewModel::SetSelectedObjectColor(const FLinearColor& InColor)
{
	if (SelectedObjectColor == InColor) return; 

	SelectedObjectColor = InColor; 
	OnSelectedColorChanged.Broadcast(SelectedObjectColor); 

	if (ManagerSubsystem)
	{
		ManagerSubsystem->UpdateSelectedActorColor(SelectedObjectColor);
	}
}

void UMainViewModel::SetSelectedObjectScale(float InScale)
{
	if (FMath::IsNearlyEqual(SelectedObjectScale, InScale))
	{
		return;
	}

	SelectedObjectScale = InScale;
	OnSelectedScaleChanged.Broadcast(SelectedObjectScale); 

	if (ManagerSubsystem)
	{
		ManagerSubsystem->UpdateSelectedActorScale(SelectedObjectScale);
	}
}

void UMainViewModel::UpdateSpawnedObjectsList(const TArray<AInteractiveObjectBase*>& UpdatedObjects)
{
	SpawnedObjects = UpdatedObjects;
	OnSpawnedObjectsChanged.Broadcast(SpawnedObjects);
}

void UMainViewModel::UpdateSelectedObject(AInteractiveObjectBase* NewSelectedObject)
{
	if (SelectedObject == NewSelectedObject)
	{
		return;
	}

	SelectedObject = NewSelectedObject;
	OnSelectedObjectChanged.Broadcast(SelectedObject);

	if (SelectedObject)
	{
		SelectedObjectColor = SelectedObject->Color;
		SelectedObjectScale = SelectedObject->Scale;

		OnSelectedColorChanged.Broadcast(SelectedObjectColor);
		OnSelectedScaleChanged.Broadcast(SelectedObjectScale);
	}
	else
	{
		// Если ничего не выбрано, сбрасываем и уведомляем
		SelectedObjectColor = FLinearColor::Black;
		SelectedObjectScale = 0.0f;
		OnSelectedColorChanged.Broadcast(SelectedObjectColor);
		OnSelectedScaleChanged.Broadcast(SelectedObjectScale);
	}
}
