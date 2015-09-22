// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG1.h"
#include "RPGCharacter.h"


// Sets default values
ARPGCharacter::ARPGCharacter()
{
   // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;

   // Création d'un Spring Arm Component 
   SpringArmComponent =CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")); 
   SpringArmComponent->AttachParent = GetCapsuleComponent(); 
   SpringArmComponent->TargetArmLength = 300; 
   FRotator rotation(-30.f, 0.f, 0.f); 
   SpringArmComponent->RelativeRotation = rotation; 
   SpringArmComponent->bEnableCameraLag = true; 
   SpringArmComponent->bEnableCameraRotationLag = true; 
   SpringArmComponent->CameraLagSpeed = 10.0f; 
   SpringArmComponent->CameraRotationLagSpeed = 10.0f;

   // Création d'un CameraComponent 
   ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>( 
      TEXT("ThirdPersonCamera")); 
   ThirdPersonCameraComponent->AttachParent = SpringArmComponent;

   // Positionner la caméra un peu au dessus des yeux 
   ThirdPersonCameraComponent->RelativeLocation = FVector(-150.0, 0, 50.0f + BaseEyeHeight);
   // Permettre au pion de contrôler la rotation 
   ThirdPersonCameraComponent->bUsePawnControlRotation = true;

   // Positionner la caméra un peu au dessus des yeux 
   ThirdPersonCameraComponent->RelativeLocation = FVector(-150.0, 0, 50.0f + BaseEyeHeight);
   // Permettre au pion de contrôler la rotation 
   ThirdPersonCameraComponent->bUsePawnControlRotation = true;

   Vitesse = 0.3f;
}


// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
   Super::BeginPlay();

   if (GEngine)
   {
      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Voici RPGCharacter!"));
   }

}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
   Super::SetupPlayerInputComponent(InputComponent);
   GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Setup"));

   // On associe des assignations du gameplay à des traitements
   InputComponent->BindAxis("Avancer", this, &ARPGCharacter::Avancer);
   InputComponent->BindAxis("VersLaDroite", this, &ARPGCharacter::VersLaDroite);

   InputComponent->BindAxis("Tourner", this, &ARPGCharacter::AddControllerYawInput);
   InputComponent->BindAxis("RegarderEnHaut", this, &ARPGCharacter::AddControllerPitchInput);


   InputComponent->BindAction("Sauter", IE_Pressed, this, &ARPGCharacter::OnStartJump);
   InputComponent->BindAction("Sauter", IE_Released, this, &ARPGCharacter::OnStopJump);

   InputComponent->BindAction("Courir", IE_Pressed, this, &ARPGCharacter::OnStartRunning); 
   InputComponent->BindAction("Courir", IE_Released, this, &ARPGCharacter::OnStopRunning);

}

void ARPGCharacter::Avancer(float Value)
{
   if ((Controller != NULL) && (Value != 0.0f))
   {
      // Trouver où est l'avant
      FRotator Rotation = Controller->GetControlRotation();
      // Ne pas tenir compte du pitch
      if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
      {
         Rotation.Pitch = 0.0f;
      }
      // Ajouter le mouvement dans la direction Avant – construire le vecteur
      const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
      AddMovementInput(Direction, Value * Vitesse);
   }
}

void ARPGCharacter::VersLaDroite(float Val)
{
   if ((Controller != NULL) && (Val != 0.0f))
   {
      // Trouver où est la droite
      const FRotator Rotation = Controller->GetControlRotation();
      const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
      // Ajouter le mouvement dans cette direction
      AddMovementInput(Direction, Val);

   }
}

void ARPGCharacter::OnStartJump()
{
   GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("dss"));
   bPressedJump = true;
}
void ARPGCharacter::OnStopJump()
{
   bPressedJump = false;
}

void ARPGCharacter::OnStartRunning() 
{ 
   Vitesse = 1.2f; bPressedRun = true; 
} 
void ARPGCharacter::OnStopRunning() 
{ 
   Vitesse = 0.5f; bPressedRun = false; 
}

bool ARPGCharacter::IsRunning() 
{ 
   return bPressedRun; 
}