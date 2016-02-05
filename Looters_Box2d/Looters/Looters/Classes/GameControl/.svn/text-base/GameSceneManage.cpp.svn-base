#include "GameSceneManage.h"

SceneManage* m_gSceneManage = NULL;

SceneManage::SceneManage()
{
}

SceneManage::~SceneManage()
{
	
	
}

SceneManage* SceneManage::GetSceneManageHendle( void )
{
	if( m_gSceneManage == NULL )
	{
		m_gSceneManage = new SceneManage();
		if( !m_gSceneManage->Init() )
		{
			delete m_gSceneManage;
			m_gSceneManage = NULL;
		}
	}
	return m_gSceneManage;
}

void SceneManage::ReleaseSceneManage( void )
{
	if( m_gSceneManage )
	{
		delete m_gSceneManage;
		m_gSceneManage = NULL;
	}
}

bool SceneManage::Init( void )
{
	m_pCentralScene = NULL;
	m_pLogicScene = NULL;

	return true;
}

bool SceneManage::RunScece( int iSceneID, bool bReplace )
{
	switch( iSceneID )
	{
	case SCENE_LOGIN:
		{
			if( m_pLogicScene == NULL )
			{
                m_pLogicScene = new LoginScene();
				if( m_pLogicScene )
					m_pLogicScene->autorelease();
				if( !m_pLogicScene ->init() )
				{
					delete m_pLogicScene;
					m_pLogicScene = NULL;
				}
			}

			if( bReplace )
				CCDirector::sharedDirector()->replaceScene(m_pLogicScene);
			else
				CCDirector::sharedDirector()->runWithScene(m_pLogicScene);

		}
		break;
	case SCENE_CENTRAL:
		{
			if( m_pCentralScene == NULL )
			{
                m_pCentralScene = new CentralScene();
				if( m_pCentralScene )
					m_pCentralScene->autorelease();
				if( !m_pCentralScene ->init() )
				{
					delete m_pCentralScene;
					m_pCentralScene = NULL;
				}
			}

			if( bReplace )
				CCDirector::sharedDirector()->replaceScene(m_pCentralScene);
			else
				CCDirector::sharedDirector()->runWithScene(m_pCentralScene);
		}
		break;
	}
	return true;
}




