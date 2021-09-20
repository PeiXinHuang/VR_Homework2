// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenCloseDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine.h"
// Sets default values for this component's properties
UOpenCloseDoor::UOpenCloseDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenCloseDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UOpenCloseDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* door = GetOwner();
	m_DefaultPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	static bool bDoorOpened = false;
	TArray<AActor*> Actors;	m_TriggerVolume->GetOverlappingActors(OUT Actors); 	

	if (Actors.Num() == 1 && Actors[0]->GetName().Find("Copper") == 0) {
	
		/*FRotator OpenRotator = FRotator(0, 90, 0);
		door->SetActorRotation(OpenRotator);    */
		if (bDoorOpened == false) {  
			OnDoorOpen.Broadcast();    
			bDoorOpened = true;
		}

	}
	else {
		/*FRotator OpenRotator = FRotator(0, 0, 0);
		door->SetActorRotation(OpenRotator);    */ 

		if (bDoorOpened) {      
			OnDoorClose.Broadcast();     
			bDoorOpened = false;
		}

	}

	// ...
	// ...
}

