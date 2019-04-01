// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun_RubyPistol.h"
#include "Components/InputComponent.h"

// Sets default values
AGun_RubyPistol::AGun_RubyPistol()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGun_RubyPistol::BeginPlay()
{
	Super::BeginPlay();
	ammoClip = 8;
	
}

// Called every frame
void AGun_RubyPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void AGun_RubyPistol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	
//	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGun_RubyPistol::Fire);
//	
//}


void AGun_RubyPistol::Fire() {
	ammoClip = 7;
}


