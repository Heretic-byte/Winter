#include "MyLib.h"
#include "Winter2Character.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/MyGameInstance.h"

UWorld* UMyLib::GetUWorld()
{
	return UMyGameInstance::Get->GetWorld();
}

AWinter2Character* UMyLib::GetPlayer()
{
	return Cast<AWinter2Character>( UGameplayStatics::GetPlayerPawn(GetUWorld(),0));
}

AMyPlayerController* UMyLib::GetPlayerCon()
{
	return Cast<AMyPlayerController>( UGameplayStatics::GetPlayerController(GetUWorld(),0));
}

//UWidgetCanvasWorld* UMyLib::GetCanvas()
//{
//	AMyHUD* HUD = Cast<AMyHUD>(GetPlayerCon()->GetHUD());
//                                                                                                                                       
//	return HUD->GetCanvas();                                                                                                               
//}

float UMyLib::SetFloatPrecision(float TheFloat, int32 Precision)
{
	if (Precision <= 0)
	{
		return roundf(TheFloat);
	}

	Precision = FMath::Clamp(Precision, 1, 10);

	int32 PresRounded = round(FMath::Pow(10, Precision));

	float A = round(TheFloat * PresRounded);
	float B = PresRounded;

	return A / B;
}

FText UMyLib::GetFloatToPercentText(float v)
{
	//v = SetFloatPrecision(v,1);
	
	bool IsMinus = v <0.f;
	
	FTextFormat FormatT;

	FFormatOrderedArguments Args;
	
	if(IsMinus)
	{
		FormatT = FText::FromString("-{0}%");	
	}
	else
	{
		FormatT = FText::FromString("+{0}%");
	}

	Args.Add(SetFloatPrecision(v*100.f,0));

	return FText::Format(FormatT,Args);
}

int UMyLib::GetRectVertIndexPer(const FSlateRect& rect, int maxDivide, const FVector2D& mousePos)
{
	float MinVert = rect.Top;//시작점
	
	float Divide = (rect.Bottom - rect.Top) / maxDivide;//한칸 높이
	
	int MaxIter = maxDivide*2;

	TArray<float>AryVertMinMax;
	
	AryVertMinMax.Init(-1,MaxIter);

	int ResultIndex = 0;

	for(int i=0;i<MaxIter;i+=2)//if 3 than 6, if result 5,0,2,4
	{
		AryVertMinMax[i] = MinVert; 
			
		AryVertMinMax[i+1] = AryVertMinMax[i] + Divide;

		if(mousePos.Y >= AryVertMinMax[i] && mousePos.Y <= AryVertMinMax[i+1])
		{
			break;
		}

		MinVert = AryVertMinMax[i+1];

		ResultIndex++;
	}

	return ResultIndex;

	//divide vertical only
	// Point.X >= Left && Point.X <= Right && Point.Y >= Top && Point.Y <= Bottom;
	//fail contains = return -1?

	
}

bool UMyLib::CheckAngle(const AActor* center, const AActor* target, float angle)
{
	float PeripheralVisionCosine = FMath::Cos(FMath::DegreesToRadians(angle));

	FVector const OtherLoc = target->GetActorLocation();

	FVector const SensorLoc = center->GetActorLocation();

	FVector const SelfToOther = OtherLoc - SensorLoc;

	FVector const SelfToOtherDir = SelfToOther.GetSafeNormal();

	FVector const MyFacingDir = center->GetActorRotation().Vector();

	return ((SelfToOtherDir | MyFacingDir) >= PeripheralVisionCosine);
}

bool UMyLib::CheckRange(const AActor* center, const AActor* target, float rangeSqr)
{
	FVector const OtherLoc = target->GetActorLocation();
	
	FVector const SensorLoc = center->GetActorLocation();
	
	FVector const SelfToOther = OtherLoc - SensorLoc;

	float const SelfToOtherDistSquared = SelfToOther.SizeSquared();
	
	if (SelfToOtherDistSquared > rangeSqr)
	{
		return false;
	}

	return true;
}

bool UMyLib::BoxOverlapActors(UObject* WorldContextObject,FRotator rot,const FVector BoxPos, FVector BoxExtent, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, UClass* ActorClassFilter, const TArray<AActor*>& ActorsToIgnore, TArray<AActor*>& OutActors)
{
	OutActors.Empty();

	TArray<UPrimitiveComponent*> OverlapComponents;
	bool bOverlapped = BoxOverlapComponents(WorldContextObject,rot,BoxPos, BoxExtent, ObjectTypes, NULL, ActorsToIgnore, OverlapComponents);
	if (bOverlapped)
	{
		UKismetSystemLibrary::GetActorListFromComponentList(OverlapComponents, ActorClassFilter, OutActors);
	}

	return (OutActors.Num() > 0);
}

bool UMyLib::BoxOverlapComponents(UObject* WorldContextObject,FRotator rot,const FVector BoxPos, FVector BoxExtent, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, UClass* ComponentClassFilter, const TArray<AActor*>& ActorsToIgnore, TArray<UPrimitiveComponent*>& OutComponents)
{
	OutComponents.Empty();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(BoxOverlapComponents), false);
	Params.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;

	FCollisionObjectQueryParams ObjectParams;
	for (auto Iter = ObjectTypes.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel & Channel = UCollisionProfile::Get()->ConvertToCollisionChannel(false, *Iter);
		ObjectParams.AddObjectTypesToQuery(Channel);
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World != nullptr)
	{
		World->OverlapMultiByObjectType(Overlaps, BoxPos, rot.Quaternion(), ObjectParams, FCollisionShape::MakeBox(BoxExtent), Params);
	}

	for (int32 OverlapIdx=0; OverlapIdx<Overlaps.Num(); ++OverlapIdx)
	{
		FOverlapResult const& O = Overlaps[OverlapIdx];
		if (O.Component.IsValid())
		{ 
			if ( !ComponentClassFilter || O.Component.Get()->IsA(ComponentClassFilter) )
			{
				OutComponents.Add(O.Component.Get());
			}
		}
	}

	return (OutComponents.Num() > 0);
}

bool UMyLib::SphereOverlapActors(UObject* WorldContextObject,FRotator Rot ,const FVector SpherePos, float SphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, UClass* ActorClassFilter, const TArray<AActor*>& ActorsToIgnore, TArray<AActor*>& OutActors)
{
	OutActors.Empty();

	TArray<UPrimitiveComponent*> OverlapComponents;
	bool bOverlapped = SphereOverlapComponents(WorldContextObject,Rot, SpherePos, SphereRadius, ObjectTypes, NULL, ActorsToIgnore, OverlapComponents);
	if (bOverlapped)
	{
		UKismetSystemLibrary::GetActorListFromComponentList(OverlapComponents, ActorClassFilter, OutActors);
	}

	return (OutActors.Num() > 0);
}

bool UMyLib::SphereOverlapComponents(UObject* WorldContextObject,FRotator Rot , const FVector SpherePos, float SphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, UClass* ComponentClassFilter, const TArray<AActor*>& ActorsToIgnore, TArray<UPrimitiveComponent*>& OutComponents)
{
	OutComponents.Empty();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(SphereOverlapComponents), false);
	Params.AddIgnoredActors(ActorsToIgnore);
	TArray<FOverlapResult> Overlaps;

	FCollisionObjectQueryParams ObjectParams;
	for (auto Iter = ObjectTypes.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel & Channel = UCollisionProfile::Get()->ConvertToCollisionChannel(false, *Iter);
		ObjectParams.AddObjectTypesToQuery(Channel);
	}


	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if(World != nullptr)
	{
		World->OverlapMultiByObjectType(Overlaps, SpherePos, Rot.Quaternion(), ObjectParams, FCollisionShape::MakeSphere(SphereRadius), Params);
	}

	for (int32 OverlapIdx=0; OverlapIdx<Overlaps.Num(); ++OverlapIdx)
	{
		FOverlapResult const& O = Overlaps[OverlapIdx];
		if (O.Component.IsValid())
		{ 
			if ( !ComponentClassFilter || O.Component.Get()->IsA(ComponentClassFilter) )
			{
				OutComponents.Add(O.Component.Get());
			}
		}
	}

	return (OutComponents.Num() > 0);
}
