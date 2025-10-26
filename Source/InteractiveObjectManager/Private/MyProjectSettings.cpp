#include "MyProjectSettings.h"

UMyProjectSettings* UMyProjectSettings::Get()
{
	return GEngine ? CastChecked<UMyProjectSettings>(GEngine->GetGameUserSettings()) : nullptr;
}
