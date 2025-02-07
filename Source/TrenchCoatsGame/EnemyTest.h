// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyTest.generated.h"

UCLASS()
class TRENCHCOATSGAME_API AEnemyTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TakeDamage(int damage);
	
	UPROPERTY(EditAnywhere)
	int health;
};
