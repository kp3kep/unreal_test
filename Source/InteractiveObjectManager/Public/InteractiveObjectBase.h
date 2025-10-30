#pragma once

#include "InteractiveObjectInterface.h"
#include "GameFramework/Actor.h"
#include "InteractiveObjectBase.generated.h"

UCLASS()
class INTERACTIVEOBJECTMANAGER_API AInteractiveObjectBase : public AActor, public IInteractiveObjectInterface
{
	GENERATED_BODY()

public:
	AInteractiveObjectBase();

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	void SetColor(const FLinearColor& InColor) { Color = InColor; }

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	void SetScale(const float InScale) { Scale = InScale; }

	// ~IInteractiveObjectInterface interface
	UFUNCTION()
	virtual void UpdateColor_Implementation(const FLinearColor& InColor) override;
	
	UFUNCTION()
	virtual void UpdateScale_Implementation(float InScale) override;

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	virtual FLinearColor GetColor_Implementation() override { return Color; }

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	virtual float GetScale_Implementation() override { return Scale; }
	// End ~IInteractiveObjectInterface

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive Object")
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive Object")
	float Scale = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactive Object|Material")
	FName ColorParameterName = TEXT("BaseColor");
};
