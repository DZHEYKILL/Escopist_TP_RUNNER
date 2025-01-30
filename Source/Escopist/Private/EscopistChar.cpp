// Fill out your copyright notice in the Description page of Project Settings.


#include "EscopistChar.h"

// Sets default values
AEscopistChar::AEscopistChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->MaxWalkSpeed = 1500;
    GetCharacterMovement()->JumpZVelocity = 850;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = true;

    bIsOnAir = false;

    WallRightLeftVelocity = 950.0f;
    WallLaunchVelocityZ = 750.0f;
    WallRunPlane = FVector (0.0f, 0.0f, 1.0f);

}


bool AEscopistChar::WallRunningSystem(int32 TraceDrct, int32 LaunchDrct, float RightLeftVelocity, float LaunchVelocityZ)
{
    bool bCanWallRun = false;

        if (bIsOnAir)
        {

            // ��������� � �������� ����� �����������
            //int32 TraceRightLeftDrct = TraceDrct;
            FVector Start = GetActorLocation();
            FVector RightVector = GetActorRightVector();
            FVector End = Start + (RightVector * TraceDrct) ;  // 1000 ������ ������

        

            // ��������� ��� �������� ���������� � ���������� �����������
            FHitResult HitResult;

            // ��������� ������ �����������
            ECollisionChannel TraceChannel = ECC_Visibility;

            // �������������� ��������� ����������� (���������� ������ ����)
            FCollisionQueryParams QueryParams;
            QueryParams.AddIgnoredActor(this);

            // ��������� �����������
        
            bool bHit = GetWorld()->LineTraceSingleByChannel(
                HitResult,       // �������� ���������
                Start,           // ��������� �����
                End,             // �������� �����
                TraceChannel,    // ����� ��������
                QueryParams     // ��������� �����������
            );

                // ���������, ��� �� ������ ��� ������
                if (AActor* HitActor = HitResult.GetActor())
                {
            
                    bCanWallRun = HitActor->IsA(AStaticMeshActor::StaticClass()) && AxisForward > 0 && bHit && bIsOnAir;
                
                    if (bCanWallRun)
                    {

                        

                        FVector Normal = HitResult.ImpactNormal;

                        vWallRunSpeed = GetActorForwardVector() * 2000.0f;
                        GetCharacterMovement()->Velocity = FVector(vWallRunSpeed.X, vWallRunSpeed.Y, 0.0f);
                        GetCharacterMovement()->SetPlaneConstraintNormal(WallRunPlane);

                        //Fix Wall Run Rotation
                        FRotator Rotation = Normal.Rotation();
                        float fYawWallRun = Rotation.Yaw + TraceDrct;
                        FRotator FixWallRunZ = FRotator(0.0f, fYawWallRun, 0.0f);
                        SetActorRotation(FixWallRunZ);

                        if (bIsJump)
                        {
                            //�� �������� ������ � ����������� TraceDrct
                            FVector LaunchMath = GetActorRightVector() * RightLeftVelocity * LaunchDrct + GetActorForwardVector();
                            /*
                            FVector Velocity = GetActorRightVector() * RightLeftVelocity;
                            FVector Direct = Velocity * LaunchDrct;
                            FVector SumWallJump = GetActorForwardVector() + Direct;q
                    
                            */
                            FVector Launch = FVector(LaunchMath.X, LaunchMath.Y, LaunchVelocityZ);
                            LaunchCharacter(Launch, false, false);
                        }

                    }
                    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);
                }
                else
                {
                    // ��� �������, ������ ����� � ������ �������
                    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 2.0f);
                }

        return bCanWallRun;

    }
    return bCanWallRun;
}

void AEscopistChar::ForwardWallClimbing(int32 TraceLength, FVector ArrowBlinkVector)
{
    // ��������� � �������� ����� �����������
            //int32 TraceRightLeftDrct = TraceDrct;
    FVector Start = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector End = Start + (ForwardVector * TraceLength);  // 1000 ������ ������



    // ��������� ��� �������� ���������� � ���������� �����������
    FHitResult HitResult;

    // ��������� ������ �����������
    ECollisionChannel TraceChannel = ECC_Visibility;

    // �������������� ��������� ����������� (���������� ������ ����)
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    // ��������� �����������

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,       // �������� ���������
        Start,           // ��������� �����
        End,             // �������� �����
        TraceChannel,    // ����� ��������
        QueryParams     // ��������� �����������
    );
    
        
        if (bHit && bIsOnAir)
        {
            //Keep On Wall
            DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);
            GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
            if (bIsJump)
            {
                //Launch
                FVector Launch = (ArrowBlinkVector * 1000) + (GetActorUpVector() * 800);
                LaunchCharacter(Launch, false, false);
                
                //SetRotation
                FVector Normal = HitResult.Normal;
                FRotator RotateWall = Normal.Rotation();
                FRotator LaunchRotation = FRotator(GetActorRotation().Roll, RotateWall.Yaw, GetActorRotation().Pitch);
                

                SetActorRotation(LaunchRotation);

            }

        }
        else
        {
            DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 2.0f);
        }


    }

    

TArray<AStaticMeshActor*> AEscopistChar::FindAllStaticMeshes()
{
    StaticMeshes.Empty();

    UWorld* World = GetWorld();

    TArray<AActor*> FoundActors;

    // ���� ��� ������ ������ AStaticMeshActor
    UGameplayStatics::GetAllActorsOfClass(World, AStaticMeshActor::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        // �������� ������ � ���� AStaticMeshActor
        AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(Actor);
        if (StaticMeshActor) // ���������, ��� �� ������� ����
        {
            StaticMeshes.Add(StaticMeshActor); // ��������� ����� � ������
        }
    }

    return StaticMeshes;

}

// Called when the game starts or when spawned
void AEscopistChar::BeginPlay()
{
	Super::BeginPlay();
    StaticMeshes = FindAllStaticMeshes();
   
}

// Called every frame
void AEscopistChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    bIsOnAir = GetCharacterMovement()->IsFalling();


   
}

// Called to bind functionality to input
void AEscopistChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}