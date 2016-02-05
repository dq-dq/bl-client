//
//  LootersAppController.h
//  Looters
//
//  Created by 宁 王 on 12-12-10.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>
#import "GameCenterManager.h"

@interface RootViewController : UIViewController
<
GameCenterManagerDelegate                              // game center 的几个接口
>
{
	GameCenterManager*	gameCenterManager;				// game center
	UILabel*			gameCenterLabel;				// game center 的一些提示信息显示
}

@property (nonatomic, retain) GameCenterManager *gameCenterManager;

//----------------------- game center 相关接口--------------------------------------------
// 初始化 game center
- (void) initGameCenter;

// 对话框函数
- (void) showAlertWithTitle: (NSString*) title forMessage:(NSString*) message;

@end
