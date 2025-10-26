#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveObjectBase.generated.h"

UCLASS()
class INTERACTIVEOBJECTMANAGER_API AInteractiveObjectBase : public AActor
{
	GENERATED_BODY()

public:
	AInteractiveObjectBase();

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	void UpdateVisuals();

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	void SetColor(const FLinearColor& InColor) { Color = InColor; }

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	void SetScale(const float InScale) { Scale = InScale; }

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	FLinearColor GetColor() const { return Color; }
	
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	float GetScale() const { return Scale; }

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
