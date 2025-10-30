#include "InteractiveObjectBase.h"

AInteractiveObjectBase::AInteractiveObjectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	RootComponent = MeshComponent;
}

void AInteractiveObjectBase::UpdateColor_Implementation(const FLinearColor& InColor)
{
	SetColor(InColor);
	
	if (!DynamicMaterialInstance)
	{
		if (UMaterialInterface* Material = MeshComponent->GetMaterial(0))
		{
			DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
			MeshComponent->SetMaterial(0, DynamicMaterialInstance);
		}
	}

	if (DynamicMaterialInstance)
	{
		DynamicMaterialInstance->SetVectorParameterValue(ColorParameterName, Color);
	}
}

void AInteractiveObjectBase::UpdateScale_Implementation(const float InScale)
{
	SetScale(InScale);
	
	MeshComponent->SetRelativeScale3D(FVector(Scale));
}

