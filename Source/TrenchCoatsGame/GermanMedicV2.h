// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GermanMedicV2.generated.h"

UCLASS()
class TRENCHCOATSGAME_API AGermanMedicV2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGermanMedicV2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TakeDamage(int damage);

	UPROPERTY(VisibleAnywhere)
		int health;
	
};
