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

	MainViewModel->Initialize(this);
	
	SettingsViewModel->LoadSettings();
}

void UInteractiveObjectManagerSubsystem::SpawnObjectInWorld(const ESpawnObjectType SelectedSpawnObjectType)
{
	const UInteractiveObjectSettings* InteractiveObjectSettings = GetDefault<UInteractiveObjectSettings>();
	if (!InteractiveObjectSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractiveObjectManagerSubsystem::SpawnObjectInWorld - Failed to get Interactive Object Project Settings!"));
		return;
	}

	UClass* ClassToSpawn = InteractiveObjectSettings->GetClassToSpawn(SelectedSpawnObjectType);

	if (!ClassToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractiveObjectManagerSubsystem::SpawnObjectInWorld - Failed to load ClassToSpawn from .ini!"));
		return;
	}

	const UMyProjectSettings* Settings = UMyProjectSettings::Get();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractiveObjectManagerSubsystem::SpawnObjectInWorld - Failed to get UMyGameUserSettings!"));
		return;
	}

	if (AInteractiveObjectBase* NewObject = SpawnActor(ClassToSpawn))
	{
		IInteractiveObjectInterface::Execute_UpdateColor(NewObject, Settings->DefaultSpawnObjectColor);
		IInteractiveObjectInterface::Execute_UpdateScale(NewObject, Settings->DefaultSpawnObjectScale);
		
		SpawnedObjectsList.Add(NewObject);
		if (MainViewModel)
		{
			MainViewModel->UpdateSpawnedObjectsList(SpawnedObjectsList);
		}
	}
}

void UInteractiveObjectManagerSubsystem::DeleteSelectedObject()
{
	if (!CurrentSelectedObject || !MainViewModel)
	{
		return;
	}

	AActor* ObjectToDelete = CurrentSelectedObject;

	SpawnedObjectsList.Remove(ObjectToDelete);
	MainViewModel->UpdateSpawnedObjectsList(SpawnedObjectsList);

	SetSelectedObject(nullptr);

	ObjectToDelete->Destroy();
}

void UInteractiveObjectManagerSubsystem::SetSelectedObject(AActor* NewSelection)
{
	if (CurrentSelectedObject == NewSelection || !MainViewModel)
	{
		return;
	}

	CurrentSelectedObject = NewSelection;

	MainViewModel->UpdateSelectedObject(CurrentSelectedObject);
}

void UInteractiveObjectManagerSubsystem::UpdateSelectedActorColor(const FLinearColor& InColor) const
{
	if (CurrentSelectedObject && CurrentSelectedObject->Implements<UInteractiveObjectInterface>())
	{
		IInteractiveObjectInterface::Execute_UpdateColor(CurrentSelectedObject, InColor);
	}
}

void UInteractiveObjectManagerSubsystem::UpdateSelectedActorScale(const float InScale) const
{
	if (CurrentSelectedObject && CurrentSelectedObject->Implements<UInteractiveObjectInterface>())
	{
		IInteractiveObjectInterface::Execute_UpdateScale(CurrentSelectedObject, InScale);
	}
}

AInteractiveObjectBase* UInteractiveObjectManagerSubsystem::SpawnActor(UClass* ClassToSpawn) const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return nullptr;
	}
	const APlayerController* PC = World->GetFirstPlayerController();
	if (!PC)
	{
		return nullptr;
	}
	const APawn* Pawn = PC->GetPawn();
	if (!Pawn)
	{
		return nullptr;
	}	

	const FVector SpawnLocation = Pawn->GetActorLocation() + Pawn->GetActorForwardVector() * 250.0f;
	AInteractiveObjectBase* NewObject = World->SpawnActor<AInteractiveObjectBase>(ClassToSpawn, SpawnLocation, FRotator::ZeroRotator);

	return NewObject;
}