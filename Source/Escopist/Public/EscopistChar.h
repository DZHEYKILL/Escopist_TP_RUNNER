// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"

#include "EscopistChar.generated.h"



UCLASS()
class ESCOPIST_API AEscopistChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEscopistChar();



	
	UFUNCTION(BlueprintCallable)
	bool WallRunningSystem(int32 TraceDrct, int32 LaunchDrct, float RightLeftVelocity,float LaunchVelocity);
	UFUNCTION(BlueprintCallable)
	TArray<AStaticMeshActor*> FindAllStaticMeshes();
	UFUNCTION(BlueprintCallable)
	void ForwardWallClimbing(int32 TraceLength, FVector ArrowBlinkVector);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	float AxisForward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	float AxisRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	float LookUp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	float Turn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	bool bIsJump;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	bool bIsOnAir;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Value")
	bool bIsRightWall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Value")
	bool bIsLeftWall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Value")
	bool bIsWallRunning;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Value")
	FVector WallRunPlane;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Value")
	FVector vWallRunSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Value")
	float WallRightLeftVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Value")
	float WallLaunchVelocityZ;


	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	TArray<AStaticMeshActor*> StaticMeshes;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
