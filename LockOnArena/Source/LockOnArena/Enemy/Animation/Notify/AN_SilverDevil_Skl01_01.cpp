// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Animation/Notify/AN_SilverDevil_Skl01_01.h"
#include "Misc/Utils.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyStateComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Skill/Enemy/EnemySkillBase.h"


UAN_SilverDevil_Skl01_01::UAN_SilverDevil_Skl01_01()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(255, 0, 0, 255);
#endif // WITH_EDITORONLY_DATA
}

void UAN_SilverDevil_Skl01_01::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AEnemyBase* Enemy = Cast<AEnemyBase>(MeshComp->GetOwner());

#if WITH_EDITOR
	if (Enemy == nullptr) { return; }
	if (GIsEditor && Enemy && Enemy->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	FEnemySkillBaseTableRow* DataTableRow = RowHandle.GetRow<FEnemySkillBaseTableRow>(TEXT("DataTableRow"));
	float ATKSkillPercent = DataTableRow->DamagePercent;

	UEnemyStateComponent* EnemyState = Enemy->GetState();

	float ATKFinal = EnemyState->GetATK() * (ATKSkillPercent / 100);

	USkeletalMeshComponent* SkeletalMeshComponent = Enemy->GetComponentByClass<USkeletalMeshComponent>();
	FVector Location = SkeletalMeshComponent->GetSocketLocation(SocketName::LeftWing);
	FRotator Rotation = SkeletalMeshComponent->GetSocketRotation(SocketName::LeftWing);

	const FName ProfileName = TEXT("Enemy");

	TArray<AActor*> IgnoreActors;
	FHitResult HitResult;


	bool bATKSuccess = UKismetSystemLibrary::SphereTraceSingleByProfile(
		MeshComp, Location, Location,
		100, ProfileName, false, IgnoreActors, EDrawDebugTrace::ForDuration,
		HitResult, true);

	if (bATKSuccess)
	{
		AActor* DamagedActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit Success"));
		UGameplayStatics::ApplyDamage(DamagedActor, ATKFinal, Enemy->GetController(), Enemy, UDamageType::StaticClass());
	}

}
