// Fill out your copyright notice in the Description page of Project Settings.

#include "RubyPistol.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"
#include "EngineUtils.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <SceneInterface.h>
#include "Engine.h"



// Sets default values
ARubyPistol::ARubyPistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pistolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pistol Mesh"));
	firingMeshPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front of Gun"));
	firingMeshPos->SetupAttachment(pistolMesh);

	firingMeshPos->SetRelativeLocation(FVector(4.0f, 0, 1.6f));

	//MESHES

	static ConstructorHelpers::FObjectFinder<UStaticMesh> pistolMeshObject(TEXT("StaticMesh'/Game/Assets/Models/Weapons/Ruby_Pistol/Final_Model/RubyPistolUV.RubyPistolUV'"));
	pistol = pistolMeshObject.Object;

	if (pistol) {
		firingMeshPos->SetStaticMesh(pistol);
	}

	//AUDIO
	static ConstructorHelpers::FObjectFinder<USoundWave> pistolShot(TEXT("SoundWave'/Game/Assets/Audio/Weapons/Pistol/gun_revolver_pistol_shot_04.gun_revolver_pistol_shot_04'"));
	pistolShotSound = pistolShot.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> pistolReload(TEXT("SoundWave'/Game/Assets/Audio/Weapons/Pistol/396331__nioczkus__1911-reload.396331__nioczkus__1911-reload'"));
	pistolReloadSound = pistolReload.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> pistolClick(TEXT("SoundWave'/Game/Assets/Audio/Weapons/Pistol/Pistol_Hammer_Cock_02.Pistol_Hammer_Cock_02'"));
	pistolClickSound = pistolClick.Object;

	pistolAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PistolAudioComponent"));
	pistolAudioComponent->bAutoActivate = false;

	if (pistolShotSound->IsValidLowLevelFast()) {
		pistolAudioComponent->SetSound(pistolShotSound);
	}

	//Particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> pistolFire(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_MuzzleFlash.P_MuzzleFlash'"));
	muzzleFlashParticle = pistolFire.Object;

	pistolParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PistolParticleSystem"));
	pistolParticleSystem->bAutoActivate = false;

	if (muzzleFlashParticle->IsValidLowLevelFast()) {
		pistolParticleSystem->SetTemplate(muzzleFlashParticle);
	}

	World = GetWorld();
	
}

// Called when the game starts or when spawned
void ARubyPistol::BeginPlay()
{
	/*playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	bBlockInput = false;*/

	for (TActorIterator<APlayerPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		playerPawnClass = *ActorItr;	
	}

	
	//EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ammoClip = 8;

	Super::BeginPlay();
	
}

// Called every frame
void ARubyPistol::Tick(float DeltaTime)
{
	
	bool rightHand = playerPawnClass->GetRightHand();

	if (currentHand) {
		nameOfHand = *currentHand->GetActorLabel();
	}

	Super::Tick(DeltaTime);	
}

void ARubyPistol::FireLeft() {
	bool leftHand = playerPawnClass->GetLeftHand();

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, nameOfHand);

	if (GEngine && leftHand) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun in hand");
		if (nameOfHand == TEXT("LeftController")) {
			if (ammoClip > 0) {
				ShootingRaycast();
				PlayGunShotAudio();
				RemoveAmmo();
			}
			else if (ammoClip == 0) {
				if (pistolClickSound->IsValidLowLevelFast()) {
					pistolAudioComponent->SetSound(pistolClickSound);
				}
				PlayGunShotAudio();
			}
		}
	}
	else if (GEngine && leftHand == false) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun not in this hand");
	}
}

void ARubyPistol::FireRight() {
	bool rightHand = playerPawnClass->GetRightHand();

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, nameOfHand);

	if (GEngine && rightHand) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun in hand");
		if (nameOfHand == TEXT("RightController")) {
			if (ammoClip > 0) {
				ShootingRaycast();
				PlayGunShotAudio();
				RemoveAmmo();

			}
			else if (ammoClip == 0) {
				if (pistolClickSound->IsValidLowLevelFast()) {
					pistolAudioComponent->SetSound(pistolClickSound);
				}
				PlayGunShotAudio();
			}
		}
	}
	else if (GEngine && rightHand == false) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Gun not in this hand");
	}
}

void ARubyPistol::ShootingRaycast() {

	FHitResult* hitResult = new FHitResult();
	FVector startingPos = firingMeshPos->GetComponentLocation();
	FVector forwardVector = firingMeshPos->GetForwardVector();
	FVector endPos = ((forwardVector * 10000) + startingPos);
	FCollisionQueryParams* traceParams = new FCollisionQueryParams;

	
		if (GetWorld()->LineTraceSingleByChannel(*hitResult, startingPos, endPos, ECC_Visibility, *traceParams))
		{
			DrawDebugLine(GetWorld(), startingPos, endPos, FColor(255, 0, 0), true);

			ACharacter* actorHit = Cast<ACharacter>(hitResult->GetActor());

			enemySoldier = Cast<AGermanSoldier>(actorHit);
			enemyMedic = Cast<AGermanMedicV2>(actorHit);

			if (enemySoldier) {
				enemySoldier->TakeDamage(20);
			}

			if (enemyMedic) {
				enemyMedic->TakeDamage(20);
			}
		}
	
}

void ARubyPistol::Reload() {
	ammoClip = 8;
	if (pistolReloadSound->IsValidLowLevelFast()) {
		pistolAudioComponent->SetSound(pistolReloadSound);
	}
	PlayGunShotAudio();
}

void ARubyPistol::RemoveAmmo() {
	
	if (pistolShotSound->IsValidLowLevelFast()) {
		pistolAudioComponent->SetSound(pistolShotSound);
	}

	ammoClip--;
}

//Get Functions

bool ARubyPistol::GetPickedUp() {
	return pickedUp;
}

int ARubyPistol::GetAmmoClip() {
	return ammoClip;
}

void ARubyPistol::PlayGunShotAudio() {
	pistolAudioComponent->Play();
}


















