#include "SettingsViewModel.h"

void USettingsViewModel::LoadSettings()
{
	const UMyProjectSettings* Settings = UMyProjectSettings::Get();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("SettingsViewModel::LoadSettings - Failed to get UMyProjectSettings!"));
		return;
	}

	SpawnObjectColor = Settings->DefaultSpawnObjectColor;
	OnSpawnColorChanged.Broadcast(SpawnObjectColor);
	
	SpawnObjectScale = Settings->DefaultSpawnObjectScale;
	OnSpawnScaleChanged.Broadcast(SpawnObjectScale);

	SpawnObjectType = Settings->DefaultSpawnObjectType;
	OnSpawnTypeChanged.Broadcast(SpawnObjectType);
}

void USettingsViewModel::SaveSettings() const
{
	UMyProjectSettings* Settings = UMyProjectSettings::Get();
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("SettingsViewModel::SaveSettings - Failed to get UMyGameUserSettings!"));
		return;
	}
	
	Settings->DefaultSpawnObjectType = SpawnObjectType;
	Settings->DefaultSpawnObjectColor = SpawnObjectColor;
	Settings->DefaultSpawnObjectScale = SpawnObjectScale;
	
	Settings->SaveSettings();
}

void USettingsViewModel::SetSpawnObjectColor(const FLinearColor& InColor)
{
	if (InColor == SpawnObjectColor)
	{
		return;
	}
	
	SpawnObjectColor = InColor;
	OnSpawnColorChanged.Broadcast(SpawnObjectColor);
}

void USettingsViewModel::SetSpawnObjectScale(float InScale)
{
	if (FMath::IsNearlyEqual(SpawnObjectScale, InScale))
	{
		return;
	}
	
	SpawnObjectScale = InScale;
	OnSpawnScaleChanged.Broadcast(SpawnObjectScale);
}

void USettingsViewModel::SetSelectedSpawnType(const FString& InString)
{
	const int32 Index = StaticEnum<ESpawnObjectType>()->GetIndexByNameString(InString);
	if (Index != INDEX_NONE)
	{
		const ESpawnObjectType NewSpawnType = StaticCast<ESpawnObjectType>(Index);
		if (SpawnObjectType != NewSpawnType)
		{
			SpawnObjectType = NewSpawnType;
			OnSpawnTypeChanged.Broadcast(SpawnObjectType);
		}
	}
}

void USettingsViewModel::SetSpawnObjectType(ESpawnObjectType InType)
{
	if (SpawnObjectType == InType || InType >= ESpawnObjectType::MAX)
	{
		return;
	}
	
	SpawnObjectType = InType;
	OnSpawnTypeChanged.Broadcast(SpawnObjectType);
}