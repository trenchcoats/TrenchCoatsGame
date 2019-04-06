// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Engine.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	playerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Player Root"));
	RootComponent = playerRoot;

	vrOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	vrOrigin->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(vrOrigin);

	camera->bLockToHmd = true;

	DefaultCharacterHeight = 160;
	FadeOutDuration = 0.1f;
	FadeInDuraction = 0.2f;

	leftHand = false;
	rightHand = false;

	BaseEyeHeight = 180;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	HMDDeviceName = GetHMDDeviceName();
	
	for (TActorIterator<ARubyPistol> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		rubyPistol = *ActorItr;
	}

	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Reload", IE_Pressed, this, &APlayerPawn::SendReloadMessage);
	InputComponent->BindAction("FireLeft", IE_Pressed, this, &APlayerPawn::SendLeftFireMessage);
	InputComponent->BindAction("FireRight", IE_Pressed, this, &APlayerPawn::SendRightFireMessage);
}



//SEND MESSAGE FUNCTIONS

void APlayerPawn::SendReloadMessage() {
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
	rubyPistol->Reload();
}

void APlayerPawn::SendLeftFireMessage() {
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
	leftHand = true;
	rubyPistol->FireLeft();
}

void APlayerPawn::SendRightFireMessage() {
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("HELLO WORLD"));
	rubyPistol->FireRight();
}

//GET FUNCTIONS

bool APlayerPawn::GetPistol() {
	return pistol;
}

FName APlayerPawn::GetHMDDeviceName() {

//This function gets the HMD Device Name


	FName deviceName;

	if (GEngine->XRSystem.IsValid()) {
		deviceName = GEngine->XRSystem->GetSystemName();
	}

	return deviceName;
}

bool APlayerPawn::GetLeftHand() {
	return leftHand;
}

bool APlayerPawn::GetRightHand() {
	return rightHand;
}








