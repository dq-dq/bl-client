#include "GameControl.h"
class GameControl* m_gGameControl = NULL;

GameControl::GameControl()
{
    CCLog("GameControl() -------- ");
}

GameControl::~GameControl()
{
    CCLog("~GameControl() -------- ");
	//释放场景管理
	SceneManage::ReleaseSceneManage();
    
    //释放路径管理
	GameFile::ReleaseGameFile();
    
    //释放声音管理
    SoundManage::ReleaseSoundManage();
}

GameControl* GameControl::GetGameControl()
{
	return m_gGameControl;
}
 
bool GameControl::RunGameControl( void )
{
	if( m_gGameControl == NULL )
	{
		m_gGameControl = new GameControl;
		if( !m_gGameControl->InitControl() )
		{
			delete m_gGameControl;
			m_gGameControl = NULL;

			return false;
		}
	}
	return true;
}


bool GameControl::InitControl()
{
    //路径
	if( GameFile::GetGameFileHandle() == NULL )
		return false;
    
	//场景
	if( SceneManage::GetSceneManageHendle() == NULL )
		return false;
    
    //声音
    if ( SoundManage::GetSoundManageHandle() == NULL )
        return false;
    
	return true;
}



void GameControl::Run( float dt )
{
    // to do
}

