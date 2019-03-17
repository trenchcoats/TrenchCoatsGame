// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Gun_RubyPistol.generated.h"

UCLASS()
class TRENCHCOATSGAME_API AGun_RubyPistol : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGun_RubyPistol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void Fire();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool pickedUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ammoClip;
	
};
