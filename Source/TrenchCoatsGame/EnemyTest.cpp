// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTest.h"


// Sets default values
AEnemyTest::AEnemyTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	health = 100;
}

// Called when the game starts or when spawned
void AEnemyTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyTest::Tick(float DeltaTime)
{
	if (health <= 0) {
		Destroy(this);
	}
	Super::Tick(DeltaTime);
}

void AEnemyTest::TakeDamage(int damage) {
	health = health - damage;
}



