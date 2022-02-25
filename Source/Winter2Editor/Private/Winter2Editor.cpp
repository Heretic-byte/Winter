﻿#include "Winter2Editor/Public/Winter2Editor.h"

class OnDataTableChanged :public INotifyOnChanged<UDataTable,FDataTableEditorUtils::EDataTableChangeInfo>//,public FDataTableEditorUtils::INotifyOnDataTableChanged
{
public:
	virtual ~OnDataTableChanged() 
	{
		Module = nullptr;
	}
	
	FWinter2EditorModule* Module;
	
	virtual void PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType)override
	{
		//Module->OnAllPlaceableAssetsChanged();
	}
	virtual void PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo ChangedType)override
	{
		//if(!Changed->RowStruct->IsChildOf(FSkillDataRow::StaticStruct()) && !Changed->RowStruct->IsChildOf(FPlayerUnitEntityRow::StaticStruct()))
		//{
		//	return;//스킬테이블이 바뀌면
		//}
		//Module->RefreshPlayerSkillData();//플레이어 테이블 변경
	}
	
	virtual void SelectionChange(const UDataTable* DataTable, FName RowName)
	{
		
	}
};

void FWinter2EditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	PropertyModule.RegisterCustomPropertyTypeLayout("MonsterUnitEntityRowHandle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDataTableRowHandleCustom::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout("ItemDataHandle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDataTableRowHandleCustom::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout("DropDataRowHandle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDataTableRowHandleCustom::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout("OptionDataHandle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDataTableRowHandleCustom::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout("ColorDataHandle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDataTableRowHandleCustom::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout("CurrencyDataHandle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDataTableRowHandleCustom::MakeInstance));


	m_OnDataTableChanged = MakeShared<OnDataTableChanged>();

	m_OnDataTableChanged->Module = this;
	
	FDataTableEditorUtils::FDataTableEditorManager::Get().AddListener(m_OnDataTableChanged.Get());

	RefreshPlayerSkillData();
	
	PropertyModule.NotifyCustomizationModuleChanged();
}//FCurrencyDataHandle

void FWinter2EditorModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	PropertyModule.UnregisterCustomPropertyTypeLayout("MonsterUnitEntityRowHandle");
	PropertyModule.UnregisterCustomPropertyTypeLayout("ItemDataHandle");
	PropertyModule.UnregisterCustomPropertyTypeLayout("DropDataRowHandle");
	PropertyModule.UnregisterCustomPropertyTypeLayout("OptionDataHandle");
	PropertyModule.UnregisterCustomPropertyTypeLayout("ColorDataHandle");
	PropertyModule.UnregisterCustomPropertyTypeLayout("CurrencyDataHandle");

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FWinter2EditorModule::RefreshPlayerSkillData()
{
	// const TArray<FName> ArySkillNames = USkillData::GetSkillTable->GetRowNames();
	//
	// for(TObjectIterator<UDataTable> classIt(EObjectFlags::RF_ClassDefaultObject,false,EInternalObjectFlags::None);classIt;++classIt)
	// {
	// 	if(!classIt->RowStruct->IsChildOf(FPlayerUnitEntityRow::StaticStruct()))
	// 	{
	// 		continue;
	// 	}
	// 	TArray<FPlayerUnitEntityRow*> AryUnits;
	// 	
	// 	classIt->GetAllRows(TEXT(""),AryUnits);
	//
	// 	for(FPlayerUnitEntityRow* Pl : AryUnits)
	// 	{
	// 		int Diff = ArySkillNames.Num() - Pl->m_ArySkillAnims.Num();
	//
	// 		while (Diff<0)
	// 		{
	// 			Pl->m_ArySkillAnims.Pop();
	// 			Diff++;
	// 		}
	// 		while (Diff>0)
	// 		{
	// 			Pl->m_ArySkillAnims.Add(FPlayerSkillAnim());
	// 			Diff--;
	// 		}
	// 		for(int i=0; i < ArySkillNames.Num(); i++)
	// 		{
	// 			const FPlayerSkillAnim* Found = Pl->m_ArySkillAnims.FindByPredicate([&](const FPlayerSkillAnim& data)
	// 			{
	// 				return data.m_SkillID == ArySkillNames[i];
	// 			});
	//
	// 			if (Found)
	// 			{
	// 				continue;//이미있으면 덮어씌우지말고 넘어가기, 애니매이션 순서 밀려나서그럼
	// 			}
	//
	// 			
	// 			Pl->m_ArySkillAnims[i].m_SkillID = ArySkillNames[i];
	// 		}
	// 	}
	// }
}

IMPLEMENT_GAME_MODULE(FWinter2EditorModule,Winter2Editor);