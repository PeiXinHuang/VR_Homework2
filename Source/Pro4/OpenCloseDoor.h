
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenCloseDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyDoorEvent);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PRO4_API UOpenCloseDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenCloseDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable)     
		FMyDoorEvent   OnDoorOpen;        
	UPROPERTY(BlueprintAssignable)     
		FMyDoorEvent   OnDoorClose;        
private:
	UPROPERTY(EditAnywhere)             
		ATriggerVolume* m_TriggerVolume; 
	AActor* m_DefaultPawn;	

};
