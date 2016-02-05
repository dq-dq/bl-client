//
//  LootersAppController.h
//  Looters
//
//  Created by 宁 王 on 12-12-10.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#import "RootViewController.h"


@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskLandscape;
#else
    return -1;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


- (void) showAlertWithTitle: (NSString*) title forMessage: (NSString*) message
{
}

- (void) initGameCenter
{
	gameCenterLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, -40, 480 - 40, 40)];
	gameCenterLabel.backgroundColor=[UIColor blackColor];
	gameCenterLabel.alpha = 0.6f;
	gameCenterLabel.textColor=[UIColor whiteColor];
	[self.view addSubview:gameCenterLabel];
	
	//是否支持 game center
	if([GameCenterManager isGameCenterAvailable])
	{
		self.gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
		[self.gameCenterManager setDelegate: self];
		[self.gameCenterManager authenticateLocalUser];//验证用户是否合法
	}
	else
	{
		[self showAlertWithTitle: @"Game Center Support Required!"
					  forMessage: @"The current device does not support Game Center, which this sample requires."];
	}
}

extern bool isLoginGC;
//用户自动登录识别的函数回调接口
- (void) processGameCenterAuth: (NSError*) error
{
	if(error == NULL)
	{
		isLoginGC=true;
		printf("processGameCenterAuth, login game center success.\n");
	}
	else
	{
		isLoginGC=false;
		printf("processGameCenterAuth, login game center error.\n");
	}
}

@end
