// Fill out your copyright notice in the Description page of Project Settings.

#include "RubyPistol.h"


// Sets default values
ARubyPistol::ARubyPistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARubyPistol::BeginPlay()
{
	Super::BeginPlay();
	ammoClip = 8;
}

// Called every frame
void ARubyPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}




