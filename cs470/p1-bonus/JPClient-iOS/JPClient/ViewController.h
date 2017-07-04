//
//  ViewController.h
//  JPClient
//
//  Created by Jarrod Parkes on 9/28/13.
//  Copyright (c) 2013 Parkes Twins. All rights reserved.
//
//  Reference: www.raywenderlich.com/3932/how-to-create-a-socket-based-iphone-app-and-server
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
    <NSStreamDelegate, UITableViewDelegate, UITableViewDataSource> {

    NSInputStream *inputStream;
    NSOutputStream *outputStream;
    NSMutableArray *commands;
}

// join view
@property (weak, nonatomic) IBOutlet UITextField *IPTextField;
@property (weak, nonatomic) IBOutlet UITextField *PortTextField;
@property (weak, nonatomic) IBOutlet UIButton *ConnectButton;

- (IBAction)PressConnect:(id)sender;

// echo view
@property (weak, nonatomic) IBOutlet UIView *EchoView;
@property (weak, nonatomic) IBOutlet UITextField *CommandTextField;
@property (weak, nonatomic) IBOutlet UIButton *SendButton;
@property (weak, nonatomic) IBOutlet UITableView *CommandTableView;

- (IBAction)PressSend:(id)sender;

@end
