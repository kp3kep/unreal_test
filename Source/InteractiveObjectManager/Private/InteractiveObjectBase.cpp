#include "InteractiveObjectBase.h"

AInteractiveObjectBase::AInteractiveObjectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	RootComponent = MeshComponent;

	MeshComponent->SetRenderCustomDepth(true);
}

void AInteractiveObjectBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UpdateVisuals();
}

void AInteractiveObjectBase::UpdateVisuals()
{
	MeshComponent->SetRelativeScale3D(FVector(Scale));

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

void AInteractiveObjectBase::OnSelected() const
{
	// MeshComponent->SetCustomDepthStencilValue(255);
}

void AInteractiveObjectBase::OnDeselected() const
{
	// MeshComponent->SetCustomDepthStencilValue(0);
}


