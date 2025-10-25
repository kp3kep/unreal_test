#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveObjectBase.generated.h"

UCLASS()
class INTERACTIVEOBJECTMANAGER_API AInteractiveObjectBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractiveObjectBase();

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	void UpdateVisuals();

	/** Функция для реакции на выделение */
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	void OnSelected() const;

	/** Функция для реакции на снятие выделения */
	UFUNCTION(BlueprintCallable, Category = "Interactive Object")
	void OnDeselected() const;

public:
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
