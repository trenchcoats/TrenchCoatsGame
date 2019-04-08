// Fill out your copyright notice in the Description page of Project Settings.

#include "GermanMedic.h"


// Sets default values
AGermanMedic::AGermanMedic()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	health = 100;
}

// Called when the game starts or when spawned
void AGermanMedic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGermanMedic::Tick(float DeltaTime)
{
	if (health <= 0) {
		Destroy(this);
	}
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGermanMedic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGermanMedic::TakeDamage(int damage) {
	health = health - damage;
}



