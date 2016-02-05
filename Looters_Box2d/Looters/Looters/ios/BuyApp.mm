//
//  BuyApp.m
//  Looters
//
//  Created by yisuode on 12-12-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "BuyApp.h"
#import "NSData+Base64.h"
#import "BuyNode.h"
//com.bw.looters.1200
//com.bw.looters.500

@implementation BuyApp

-(void)buyapp:(NSString*)_str
{
    //---------------------  
    //----监听购买结果  
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];  
    
    
    
    //申请购买   
    if ([SKPaymentQueue canMakePayments]) {  
        NSArray *product = nil;  
        strID = [NSString stringWithString:_str];
        
        product=[[NSArray alloc] initWithObjects:_str,nil]; 
        
        
        NSSet *nsset = [NSSet setWithArray:product];  
        SKProductsRequest *request=[[SKProductsRequest alloc] initWithProductIdentifiers: nsset];  
        request.delegate=self;  
        [request start];  
        [product release];    
    }  
    else  
    {  
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert"   
                                                            message:@"You can‘t purchase in app store（Himi说你没允许应用程序内购买）"                                                          
                                                           delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];  
        
        [alerView show];  
        [alerView release];  
    } 

} 

-(bool)CanMakePay  
{  
    return [SKPaymentQueue canMakePayments];  
}  

//<SKProductsRequestDelegate> 请求协议  
//收到的产品信息  
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{  
    
    NSLog(@"-----------收到产品反馈信息--------------");  
    NSArray *myProduct = response.products;  
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);  
    NSLog(@"产品付费数量: %d", [myProduct count]);  
    // populate UI   
    for(SKProduct *product in myProduct){  
        NSLog(@"product info");  
        NSLog(@"SKProduct 描述信息%@", [product description]);     
        NSLog(@"产品标题 %@" , product.localizedTitle);  
        NSLog(@"产品描述信息: %@" , product.localizedDescription);  
        NSLog(@"价格: %@" , product.price);  
        NSLog(@"Product id: %@" , product.productIdentifier);   
    }   
    SKPayment *payment = nil;   
    
    
    payment  = [SKPayment paymentWithProductIdentifier:strID];
    
    
    [[SKPaymentQueue defaultQueue] addPayment:payment];    
    [request autorelease];   
    
}  
- (void)requestProUpgradeProductData  
{  
    NSSet *productIdentifiers = [NSSet setWithObject:@"com.productid"];  
    SKProductsRequest* productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];  
    productsRequest.delegate = self;  
    [productsRequest start];   
    
}  
//弹出错误信息  
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error{  
    
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:[error localizedDescription]  
                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];  
    [alerView show];  
    [alerView release];  
}  

-(void) requestDidFinish:(SKRequest *)request   
{  
    NSLog(@"----------反馈信息结束--------------");  
    
}  

-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction{  

    NSArray *transactions =[[NSArray alloc] initWithObjects:transaction, nil];  
    [self paymentQueue:[SKPaymentQueue defaultQueue] updatedTransactions:transactions];  
    [transactions release];  
}   


- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions//交易结果  
{  

    for (SKPaymentTransaction *transaction in transactions)  
    {  
        switch (transaction.transactionState)  
        {   
            case SKPaymentTransactionStatePurchased://交易完成   
            {
                [self completeTransaction:transaction]; 
                
            
                NSLog(@"%@",transaction.transactionReceipt);
                
                NSString*encodingStr = [transaction.transactionReceipt base64EncodedString];
                
//                string ap([encodingStr UTF8String]);
                const char * encodChar = [encodingStr UTF8String];
               
                BuyNode::sharedBuyNode()->setEncodChar(encodChar);
                
                
                UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert"   
                                                                    message:@"购买成功"                                                        
                                                                   delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];  
                
                [alerView show];  
                [alerView release];   
            }
                break;   
            case SKPaymentTransactionStateFailed://交易失败  
            {
                [self failedTransaction:transaction];  
                
                UIAlertView *alerView2 =  [[UIAlertView alloc] initWithTitle:@"Alert"   
                                                                     message:@"购买失败"                                                        
                                                                    delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];  
                
                [alerView2 show];  
                [alerView2 release];
            }  
                break;   
            case SKPaymentTransactionStateRestored://已经购买过该商品   
            {
                [self restoreTransaction:transaction];  
            }
                break;
            case SKPaymentTransactionStatePurchasing:      //商品添加进列表  

                break;  
            default:  
                break;  
        }  
    }  
}  
- (void) completeTransaction: (SKPaymentTransaction *)transaction  

{  

    // Your application should implement these two methods.  
    NSString *product = transaction.payment.productIdentifier;  
    if ([product length] > 0) {  
        
        NSArray *tt = [product componentsSeparatedByString:@"."];  
        NSString *bookid = [tt lastObject];  
        if ([bookid length] > 0) {  
            [self recordTransaction:bookid];  
            [self provideContent:bookid];  
        }  
    }  
    
    // Remove the transaction from the payment queue.  
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];  
    
}  

//记录交易  
-(void)recordTransaction:(NSString *)product{  

}  

//处理下载内容  
-(void)provideContent:(NSString *)product{  
 
}  

- (void) failedTransaction: (SKPaymentTransaction *)transaction{  
    NSLog(@"失败");  
    if (transaction.error.code != SKErrorPaymentCancelled)  
    {  
    }  
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];  
    
    
}  
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction{  
    
}  

- (void) restoreTransaction: (SKPaymentTransaction *)transaction  

{  
    NSLog(@" 交易恢复处理");  
    
}  

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error{  
 
}  


#pragma mark connection delegate  
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data  
{  
    NSLog(@"%@",  [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease]);   
}  
- (void)connectionDidFinishLoading:(NSURLConnection *)connection{  
    
}  

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response{  
    switch([(NSHTTPURLResponse *)response statusCode]) {  
        case 200:  
        case 206:  
            break;  
        case 304:   
            break;  
        case 400:   
            break;    
        case 404:  
            break;  
        case 416:  
            break;  
        case 403:  
            break;  
        case 401:  
        case 500:  
            break;  
        default:  
            break;  
    }          
}  

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {  
    NSLog(@"test");  
}  

-(void)dealloc  
{  
    [super dealloc];  
}   
@end
