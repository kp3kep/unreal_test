#pragma once

#include "UObject/Interface.h"
#include "InteractiveObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UInteractiveObjectInterface : public UInterface
{
	GENERATED_BODY()
};

class INTERACTIVEOBJECTMANAGER_API IInteractiveObjectInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateScale(float InScale);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FLinearColor GetColor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetScale();
};
