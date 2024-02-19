#include "LoginSubsystem.h"


bool ULoginSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}
 
void ULoginSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}
 
void ULoginSubsystem::Deinitialize()
{
	Super::Deinitialize();
}






//RegisterPackage(s2cRoleList, S2CRoleList, ULoginSubsystem::OnS2CRoleList)