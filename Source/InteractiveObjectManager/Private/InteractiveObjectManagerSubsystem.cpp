#include "InteractiveObjectManagerSubsystem.h"
#include "MainViewModel.h"
#include "SettingsViewModel.h"
#include "InteractiveObjectBase.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void UInteractiveObjectManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	MainViewModel = NewObject<UMainViewModel>(this);
	SettingsViewModel = NewObject<USettingsViewModel>(this);

	MainViewModel->Initialize(this, SettingsViewModel); // Даем MainVM ссылку на нас
	
	SettingsViewModel->LoadSettings();
}

void UInteractiveObjectManagerSubsystem::SpawnObjectInWorld(ESpawnObjectType SelectedSpawnObjectType)
{
	const UMyProjectSettings* SettingsObject = UMyProjectSettings::Get();
	UClass* ClassToSpawn = SettingsObject->GetClassToSpawn(SelectedSpawnObjectType);

	if (!ClassToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load ClassToSpawn from .ini!"));
		return;
	}
	
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	const APlayerController* PC = World->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}
	const APawn* Pawn = PC->GetPawn();
	if (!Pawn)
	{
		return;
	}	

	const FVector SpawnLocation = Pawn->GetActorLocation() + Pawn->GetActorForwardVector() * 250.0f;
	
	if (AInteractiveObjectBase* NewObject = World->SpawnActor<AInteractiveObjectBase>(ClassToSpawn, SpawnLocation, FRotator::ZeroRotator))
	{
		NewObject->Color = SettingsObject->DefaultSpawnObjectColor;
		NewObject->Scale = SettingsObject->DefaultSpawnObjectScale;
		NewObject->UpdateVisuals();
		
		SpawnedObjectsList.Add(NewObject);
		if (MainViewModel)
		{
			MainViewModel->UpdateSpawnedObjectsList(SpawnedObjectsList);
		}
	}
}

void UInteractiveObjectManagerSubsystem::SetSelectedObject(AInteractiveObjectBase* NewSelection)
{
	if (CurrentSelectedObject == NewSelection || !MainViewModel)
	{
		return;
	}

	// Снимаем выделение со старого
	if (CurrentSelectedObject)
	{
		CurrentSelectedObject->OnDeselected();
	}

	CurrentSelectedObject = NewSelection;

	// Выделяем новый
	if (CurrentSelectedObject)
	{
		CurrentSelectedObject->OnSelected();
	}

	// Сообщаем ViewModel (и UI) об изменении
	MainViewModel->UpdateSelectedObject(CurrentSelectedObject);
}

void UInteractiveObjectManagerSubsystem::UpdateSelectedActorColor(const FLinearColor& InColor) const
{
	if (!CurrentSelectedObject)
	{
		return;
	}

	CurrentSelectedObject->Color = InColor;

	CurrentSelectedObject->UpdateVisuals();
}
void UInteractiveObjectManagerSubsystem::UpdateSelectedActorScale(float InScale) const
{
	if (!CurrentSelectedObject)
	{
		return;
	}

	CurrentSelectedObject->Scale = InScale;

	CurrentSelectedObject->UpdateVisuals();
}

