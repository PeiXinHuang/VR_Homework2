// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Left mouse button is pressed!"));
	FHitResult Hit = LineTrace();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
	if (Hit.GetActor() && PhysicsHandle)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,  
			NAME_None,       
			ComponentToGrab->GetOwner()->GetActorLocation(), 
			GetOwner()->GetActorRotation() 
		);
	}
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Left mouse button is released!"));
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}

}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InputComponent = GetOwner()->
		FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this,
			&UGrabber::Grab);   
		InputComponent->BindAction("Grab", IE_Released, this,
			&UGrabber::Release); 
	}
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


FVector UGrabber::GetLineStart() {
	FVector StartPoint;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		StartPoint, Rotation);    
	return StartPoint;
}
FVector UGrabber::GetLineEnd() {
	FVector StartPoint, EndPoint;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		StartPoint, Rotation);
	EndPoint = StartPoint + Rotation.Vector() * 100;
	return EndPoint;
}
FHitResult UGrabber::LineTrace()
{
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit, GetLineStart(), GetLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);
	return Hit;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	DrawDebugLine(GetWorld(),
		GetLineStart(),    
		GetLineEnd(),       
		FColor(0, 255, 0),
		false, 0, 0, 5);
	
	FHitResult Hit = LineTrace();   
	AActor* Actor = Hit.GetActor();
	if (Actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Hit:%s"), *Actor->GetName());
	}
	FVector StartPoint;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		StartPoint, Rotation);
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetLineEnd());
		PhysicsHandle->SetTargetRotation(Rotation);
	}

	// ...
}

