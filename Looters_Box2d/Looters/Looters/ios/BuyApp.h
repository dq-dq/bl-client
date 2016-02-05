//
//  BuyApp.h
//  Looters
//
//  Created by yisuode on 12-12-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>  
#import <StoreKit/StoreKit.h>    


@interface BuyApp : NSObject<SKProductsRequestDelegate,SKPaymentTransactionObserver>
{  
    NSString* strID;
}  
-(void) buyapp:(NSString*)_str;
- (void) requestProUpgradeProductData;    
-(bool)CanMakePay;                                 
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;  
-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction;  
- (void) completeTransaction: (SKPaymentTransaction *)transaction;  
- (void) failedTransaction: (SKPaymentTransaction *)transaction;  
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;  
-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;  
- (void) restoreTransaction: (SKPaymentTransaction *)transaction;  
-(void)provideContent:(NSString *)product;  
-(void)recordTransaction:(NSString *)product;  
@end  