#include "InteractiveObjectBase.h"
#include "MyProjectSettings.h"

UMyProjectSettings* UMyProjectSettings::Get()
{
	return GEngine ? CastChecked<UMyProjectSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

UClass* UMyProjectSettings::GetClassToSpawn(const ESpawnObjectType SelectedSpawnObjectType) const
{
	switch (SelectedSpawnObjectType)
	{
	case ESpawnObjectType::Cube:
		return CubeClassToSpawn.LoadSynchronous();
	case ESpawnObjectType::Sphere:
		return SphereClassToSpawn.LoadSynchronous();
	default:
		return nullptr;
	}
}
