#include "InteractiveObjectSettings.h"

#include "MyProjectSettings.h"

UClass* UInteractiveObjectSettings::GetClassToSpawn(const ESpawnObjectType SelectedSpawnObjectType) const
{
	switch (SelectedSpawnObjectType)
	{
	case ESpawnObjectType::Cube:
		return CubeClassToSpawn.LoadSynchronous();
	case ESpawnObjectType::Sphere:
		return SphereClassToSpawn.LoadSynchronous();
	case ESpawnObjectType::Cylinder:
		return CylinderClassToSpawn.LoadSynchronous();
	case ESpawnObjectType::Cone:
		return ConeToSpawn.LoadSynchronous();
	default:
		return nullptr;
	}
}
