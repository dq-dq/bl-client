#include "NetMessageRequest.h"
#include "NetGoogleFilter.h"
#include "NetMessageManager.h"
#include "BuildingBase.h"
#include "CentralLayer.h"
#include "Until.h"
#include "GameDebug.h"
#include "BuyNode.h"
NetMessageRequest::NetMessageRequest()
{

}

NetMessageRequest::~NetMessageRequest()
{

}

bool NetMessageRequest::SendUserLoginRequest( string mailAddress, string language, string version, string machineNum  )
{
    
    if (NotNetworking) {
        return false;
    }
    
	message::UserLoginRequest *userLogin_request = message::UserLoginRequest::default_instance().New();
	userLogin_request->set_mailaddress( mailAddress );
	userLogin_request->set_language( language );
	userLogin_request->set_version(version);
	userLogin_request->set_machinenum(machineNum);
	userLogin_request->set_instance_id(1);




	if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game,(Message*)userLogin_request) )
		return true;

	return true;
}

bool NetMessageRequest::SendDownloadMapInforRequest(string mailAddress)
{
    if (NotNetworking) {
        return false;
    }
    message::DownloadMapInforRequest *downloadMapInfor_request = message::DownloadMapInforRequest::default_instance().New();
    downloadMapInfor_request->set_mailaddress(mailAddress);
    
    if (NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game, (Message*)downloadMapInfor_request)) {
        return true;
    }
    return true;
}

bool NetMessageRequest::SendDownloadBattleInforRequest(string mailAddress,string battleCouont)
{
    if (NotNetworking) {
        return false;
    }
    message::DownloadBattleInforRequest *downloadBattleInfor_request = message::DownloadBattleInforRequest::default_instance().New();
    downloadBattleInfor_request->set_mailaddress(mailAddress);
    downloadBattleInfor_request->set_battlecouont(battleCouont);
    
    if (NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game, (Message*)downloadBattleInfor_request)) {
        return true;
    }
    return true;
}

bool NetMessageRequest::SendProduceSoldiersRequest(string version,string mailAddress)
{
    if (NotNetworking) {
        return false;
    }
    CentralLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;

    if (pLayer == NULL) return false;
    

    
    message::ProduceSoldiersRequest *produceSoldiers_request = message::ProduceSoldiersRequest::default_instance().New();
    

    produceSoldiers_request->set_mailaddress(mailAddress);
    
    
    RepeatedPtrField< ::message::ProduceSoldiersRequest_ProduceSoldiers>*  soldiersList = produceSoldiers_request->mutable_soldierslist();
	
    if (pLayer->m_building == NULL) return false;
    if (pLayer->m_building->m_UpPeopleSoldiers == NULL) return false;
    
    int num = (int)pLayer->m_building->m_UpPeopleSoldiers->size();
    
    if (num < 1) return false;
    
    for (int i = 0; i <num; i++) 
    {
     
        message::ProduceSoldiersRequest_ProduceSoldiers *produceSoldiersRequest_ProduceSoldiers = new message::ProduceSoldiersRequest_ProduceSoldiers();
        
        produceSoldiersRequest_ProduceSoldiers->set_character_id(pLayer->m_building->m_UpPeopleSoldiers->at(i)->tyep);
        produceSoldiersRequest_ProduceSoldiers->set_uuid(pLayer->m_building->m_UpPeopleSoldiers->at(i)->uuid);
        produceSoldiersRequest_ProduceSoldiers->set_produce_count(pLayer->m_building->m_UpPeopleSoldiers->at(i)->num);
        produceSoldiersRequest_ProduceSoldiers->set_index(pLayer->m_building->m_UpPeopleSoldiers->at(i)->index);
        
        
        soldiersList->AddAllocated(produceSoldiersRequest_ProduceSoldiers);
        
    }
    
    
    for (int i = 0; i <num; i++)
    {
        delete pLayer->m_building->m_UpPeopleSoldiers->at(i);
	}
	pLayer->m_building->m_UpPeopleSoldiers->clear();
    
    if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game,(Message*)produceSoldiers_request) )
		return true;
    
    return true;
}
bool NetMessageRequest::SendOperateSequenceRequest(string version,string mailAddress)
{
    if (NotNetworking) {
        return false;
    }
    message::OperateSequenceRequest *operateSequence_request = message::OperateSequenceRequest::default_instance().New();

    operateSequence_request->set_version(version);
    operateSequence_request->set_mailaddress(mailAddress);
    
    CentralLayer* pLayer = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    
    	
    int num = (int)pLayer->m_Account->size();
    if (num>0)
    {
        //加载操作列表
        RepeatedPtrField< ::message::OperateSequenceRequest_Operate>*  operatorList = operateSequence_request->mutable_operatelist();
        
        for( int i = 0; i < num; i++ )
        {
            message::OperateSequenceRequest_Operate *operateSequenceRequest_Operate = new message::OperateSequenceRequest_Operate();
            
            
            operateSequenceRequest_Operate->set_type(pLayer->m_Account->at(i)->type);
            operateSequenceRequest_Operate->set_uuid(pLayer->m_Account->at(i)->uuid);
            operateSequenceRequest_Operate->set_building_id(pLayer->m_Account->at(i)->building_id);
            operateSequenceRequest_Operate->set_move_to_map_index_x(pLayer->m_Account->at(i)->move_to_map_index_x);
            operateSequenceRequest_Operate->set_move_to_map_index_y(pLayer->m_Account->at(i)->move_to_map_index_y);
            operateSequenceRequest_Operate->set_operation_time(Until::millisecondNow_time(pLayer->m_Account->at(i)->operation_time));
            operateSequenceRequest_Operate->set_end_time(Until::millisecondNow_time(pLayer->m_Account->at(i)->end_time));
            operateSequenceRequest_Operate->set_character_id(pLayer->m_Account->at(i)->character_id);
            operateSequenceRequest_Operate->set_produce_count(pLayer->m_Account->at(i)->produce_count);
            operateSequenceRequest_Operate->set_remaining_time(Until::millisecondNow_time(pLayer->m_Account->at(i)->remaining_time));
            operateSequenceRequest_Operate->set_build_upgrade_status(pLayer->m_Account->at(i)->build_upgrade_status);
            operateSequenceRequest_Operate->set_treasure_id(pLayer->m_Account->at(i)->treasure_id);
            
            CCLOG("操作类型=============%d",pLayer->m_Account->at(i)->type);
            if (pLayer->m_Account->at(i)->type == OperateType_UpgradeSoldiers)
            {
                CCLOG("升级时间=============%s",operateSequenceRequest_Operate->operation_time().c_str());
            }
            
            operatorList->AddAllocated(operateSequenceRequest_Operate);
            
        }
    }
    
    
    num = (int)pLayer->m_Accelerated->size();
    if (num>0) 
    {
        //加载加速列表
        RepeatedPtrField< ::message::OperateSequenceRequest_Accelerate>*  accelerateList = operateSequence_request->mutable_acceleratelist();
        
        
        
        for (int i = 0; i < num ; i++) 
        {
            message::OperateSequenceRequest_Accelerate *operateSequenceRequest_Accelerate = new message::OperateSequenceRequest_Accelerate();
            operateSequenceRequest_Accelerate->set_id(pLayer->m_Accelerated->at(i)->building_id);
            operateSequenceRequest_Accelerate->set_type(pLayer->m_Accelerated->at(i)->tyep);
            operateSequenceRequest_Accelerate->set_uuid(pLayer->m_Accelerated->at(i)->uuid);
            operateSequenceRequest_Accelerate->set_gem_count(pLayer->m_Accelerated->at(i)->gem_count);
            
//            char str_time[64];
//            sprintf(str_time,"%ld",pLayer->m_Accelerated->at(i)->remain_time);
//            string result=str_time;
            
            operateSequenceRequest_Accelerate->set_remain_time(Until::millisecondNow_time(pLayer->m_Accelerated->at(i)->remain_time));
            if (pLayer->m_Accelerated->at(i)->tyep == AccelerateType_UPBuilding)
            {
                CCLOG("加速时间=============%s",operateSequenceRequest_Accelerate->remain_time().c_str());
            }
            accelerateList->AddAllocated(operateSequenceRequest_Accelerate);
        }
    }
    
    

    

    
    if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game,(Message*)operateSequence_request) )
		return true;
    
    return true;
}

bool NetMessageRequest::SendBattleMatchingRequest(string mailAddress,string previousMailAddress,string str_md5,int battle_status)
{
    if (NotNetworking) {
        return false;
    }
    message::BattleMatchingRequest *battleMatching_request = message::BattleMatchingRequest::default_instance().New();
	battleMatching_request->set_mailaddress( mailAddress );
    battleMatching_request->set_previousmailaddress(previousMailAddress);
    battleMatching_request->set_battle_status(battle_status);
    
	if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game,(Message*)battleMatching_request) )
		return true;
    return true;
}

bool NetMessageRequest::SendUploadBattleResultRequest(string mailAddress)
{
    if (NotNetworking) {
        return false;
    }
    CentralLayer* ldata = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralLayer;
    CentralData* data = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
    
    message::UploadBattleResultRequest *uploadBattleResultRequest = message::UploadBattleResultRequest::default_instance().New();
    uploadBattleResultRequest->set_mailaddress(mailAddress);
    uploadBattleResultRequest->set_golden_count(ldata->battle_golden_count);
    uploadBattleResultRequest->set_elixir_count(ldata->battle_elixir_count);
    if (ldata->battle_star_count == 0) {
        uploadBattleResultRequest->set_pvp_mark(data->m_MatchPlayer->lose_pvp_mark);
    }
    else{
        uploadBattleResultRequest->set_pvp_mark(data->m_MatchPlayer->pvp_mark);
    }
    uploadBattleResultRequest->set_star_percent(ldata->battle_curbuildcount*1.0f/ldata->battle_loadbuildcount*100);
    uploadBattleResultRequest->set_star_count(ldata->battle_star_count);
    uploadBattleResultRequest->set_use_clans_flag(false);
   
    
    
    RepeatedPtrField< ::message::UploadBattleResultRequest_BuildDestoryStatus>*  buildDestoryStatusList = uploadBattleResultRequest->mutable_builddistorystatuslist();
    
    CentralData::userMapData_t::iterator pos;
	for( pos = data->m_M_UserMapData.begin(); pos != data->m_M_UserMapData.end(); ++pos )
	{
        message::UploadBattleResultRequest_BuildDestoryStatus *uploadBattleResultRequest_BuildDestoryStatus = new message::UploadBattleResultRequest_BuildDestoryStatus();
        
        CentralData::M_UserMapData& obj = pos->second;
        if(obj.building_id == RESOURCE_GOLDMINE || obj.building_id == RESOURCE_GOLDSTORAGE
           || obj.building_id == RESOURCE_ELIXIRPUMP || obj.building_id == RESOURCE_ELIXIRSTORAGE || obj.building_id == BUILDINGTYPE_TOWNHALL)
        {
            uploadBattleResultRequest_BuildDestoryStatus->set_uuid(obj.uniqueness_build_id);
            uploadBattleResultRequest_BuildDestoryStatus->set_building_id(obj.building_id);
            uploadBattleResultRequest_BuildDestoryStatus->set_map_index_x(obj.map_index_x);
            uploadBattleResultRequest_BuildDestoryStatus->set_map_index_y(obj.map_index_y);
            uploadBattleResultRequest_BuildDestoryStatus->set_destory_status(obj.destory_status);
            uploadBattleResultRequest_BuildDestoryStatus->set_lose_count(obj.cut_collect_count);
            uploadBattleResultRequest_BuildDestoryStatus->set_lose_elixir_count(obj.cut_elixir_count);
            buildDestoryStatusList->AddAllocated(uploadBattleResultRequest_BuildDestoryStatus);
        }
        else if(obj.destory_status == 0)
        {
            uploadBattleResultRequest_BuildDestoryStatus->set_uuid(obj.uniqueness_build_id);
            uploadBattleResultRequest_BuildDestoryStatus->set_building_id(obj.building_id);
            uploadBattleResultRequest_BuildDestoryStatus->set_map_index_x(obj.map_index_x);
            uploadBattleResultRequest_BuildDestoryStatus->set_map_index_y(obj.map_index_y);
            uploadBattleResultRequest_BuildDestoryStatus->set_destory_status(obj.destory_status);
            
            buildDestoryStatusList->AddAllocated(uploadBattleResultRequest_BuildDestoryStatus);
        }
	}
    
    
    RepeatedPtrField< ::message::UploadBattleResultRequest_CharacterUsedStatus>*  characterUsedStatusList = uploadBattleResultRequest->mutable_characterusedstatuslist();
    int sospnum = (int)data->m_AttackerSoldiersAndSpell->size();
    for (int i = 0; i <sospnum; i++)
    {
        message::UploadBattleResultRequest_CharacterUsedStatus *uploadBattleResultRequest_CharacterUsedStatus = new message::UploadBattleResultRequest_CharacterUsedStatus();
        
        CentralData::AttackerSoldiersAndSpell* obj = data->m_AttackerSoldiersAndSpell->at(i);
        uploadBattleResultRequest_CharacterUsedStatus->set_characteridorspellid(obj->characterIdOrSpellId);
        uploadBattleResultRequest_CharacterUsedStatus->set_count(obj->maxcount-obj->count);
        uploadBattleResultRequest_CharacterUsedStatus->set_used_type(obj->used_type);
        
        
        characterUsedStatusList->AddAllocated(uploadBattleResultRequest_CharacterUsedStatus);
    }
    
    
    if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game,(Message*)uploadBattleResultRequest) )
		return true;

    return true;
}

bool NetMessageRequest::SendBattleStartRequest(string attackMailAddress,string defenceMailAddress,string start_battle_time)
{
    if (NotNetworking) {
        return false;
    }
    message::BattleStartRequest *battleStartRequest_request = message::BattleStartRequest::default_instance().New();
    battleStartRequest_request->set_mailaddress(attackMailAddress);
    battleStartRequest_request->set_defencemailaddress(defenceMailAddress);
    battleStartRequest_request->set_start_battle_time(start_battle_time);
    
	if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game,(Message*)battleStartRequest_request) )
		return true;
    return true;
}
bool NetMessageRequest::SendRechargeRequest(string receipt)
{
    if (NotNetworking) {
        return false;
    }
    message::RechargeRequest *rechargeRequest = message::RechargeRequest::default_instance().New();
    string macAddress = CCUserDefault::sharedUserDefault()->getStringForKey("macaddress");
    rechargeRequest->set_mailaddress(macAddress);
    rechargeRequest->set_gamemailaddress(GameData::m_stUserData->gamecenter_id);
    rechargeRequest->set_receipt(BuyNode::sharedBuyNode()->encod);
    rechargeRequest->set_buy_gem_count(BuyNode::sharedBuyNode()->num);
    rechargeRequest->set_pay_money(BuyNode::sharedBuyNode()->Rmb);

    
	if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Bank,(Message*)rechargeRequest) )
		return true;
    return true;
}

bool NetMessageRequest::SendRevengeBattleRequest(string attackMailAddress,string defenceMailAddress)
{
    if (NotNetworking) {
        return false;
    }
    message::RevengeBattleRequest *revengeBattleRequest = message::RevengeBattleRequest::default_instance().New();
    
    revengeBattleRequest->set_mailaddress(attackMailAddress);
    revengeBattleRequest->set_defencemailaddress(defenceMailAddress);
    
    if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game,(Message*)revengeBattleRequest) )
		return true;
    
    
    return true;
}

bool NetMessageRequest::SendUploadBattleFlowRequest(string defenceMailAddress,string attackMailAddress, int maxSize, int maxIndex, int index,  char *data)
{
    if (NotNetworking) {
        return false;
    }
    message::UploadBattleFlowRequest *uploadBattleFlowRequest = message::UploadBattleFlowRequest::default_instance().New();
    
    uploadBattleFlowRequest->set_attackmailaddress(attackMailAddress);
    uploadBattleFlowRequest->set_defencemailaddress(defenceMailAddress);
    
    CentralData* pCentralData = SceneManage::GetSceneManageHendle()->m_pCentralScene->m_pCentralData;
	uploadBattleFlowRequest->set_battleid(pCentralData->m_BattleStartResponseData.battleId);	

	
	message::UploadBattleFlowRequest_IoData* pData = uploadBattleFlowRequest->mutable_iodata();
	pData->add_data(data,maxSize);
	
	uploadBattleFlowRequest->set_maxindex(maxIndex);
	uploadBattleFlowRequest->set_index(index);

    if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_File,(Message*)uploadBattleFlowRequest) )
		return true;
    
    return true;
}

bool NetMessageRequest::SendIoFileRequest(int verifyCode,string requiredFile,int index)
{
    if (NotNetworking) {
        return false;
    }
    message::IoFileRequest *ioFileRequest = message::IoFileRequest::default_instance().New();
    
    ioFileRequest->set_requiredfile(requiredFile);
    ioFileRequest->set_verifycode(verifyCode);
    ioFileRequest->set_index(index);
    
    if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_File,(Message*)ioFileRequest) )
		return true;

    return true;
}

bool NetMessageRequest::SendCancleBattleRequest(string mailAddress)
{
    if (NotNetworking) {
        return false;
    }
    message::CancleBattleRequest *cancleBattleRequest = message::CancleBattleRequest::default_instance().New();
    
    cancleBattleRequest->set_mailaddress(mailAddress);
    if( NetGoogleFilter::Creater__MSG_PERSON__With__MSG_BODY_( Socket_Game,(Message*)cancleBattleRequest) )
		return true;
    
    return true;
}
