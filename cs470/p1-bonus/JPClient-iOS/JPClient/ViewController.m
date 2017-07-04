//
//  ViewController.m
//  JPClient
//
//  Created by Jarrod Parkes on 9/28/13.
//  Copyright (c) 2013 Parkes Twins. All rights reserved.
//
//  Reference: www.raywenderlich.com/3932/how-to-create-a-socket-based-iphone-app-and-server
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    commands = [[NSMutableArray alloc] init];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)initNetworkCommunication:(NSString *)ip
                            port:(NSString *)port {
    
    // create client socket with I/O streams
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    CFStreamCreatePairWithSocketToHost(NULL, (__bridge CFStringRef)ip, [port intValue], &readStream, &writeStream);
    inputStream = (__bridge NSInputStream *)readStream;
    outputStream = (__bridge NSOutputStream *)writeStream;
    
    // let this class implement/handle the I/O steam functions
    [inputStream setDelegate:self];
    [outputStream setDelegate:self];
    
    // set streams to have processing in the run loop
    [inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    // open the streams =D!
    [inputStream open];
    [outputStream open];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"ChatCellIdentifier";
    
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }

    // set table cells to contents of command, and set the font
    NSString *s = (NSString *)[commands objectAtIndex:indexPath.row];
    cell.textLabel.text = s;
    cell.textLabel.font=[UIFont fontWithName:@"Arial" size:12];
    
	return cell;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return commands.count;
}

// stream event handler (NOTE: applies to both input and output stream!)
// so, unless specifically checked, certain events will fire twice!
- (void)stream:(NSStream *)theStream handleEvent:(NSStreamEvent)streamEvent {
    
    static int startCount = 0;
    BOOL showAlert = FALSE;
    
	switch (streamEvent) {
            
        // stream connects, remove existing commands, push EchoView to front
		case NSStreamEventOpenCompleted:
			NSLog(@"Stream opened");
            [commands removeAllObjects];
            [self.view bringSubviewToFront:_EchoView];
			break;
        
        // stream (input stream) has data available
		case NSStreamEventHasBytesAvailable:
			if (theStream == inputStream) {
                
                uint8_t buffer[1024];
                int len;
                
                while ([inputStream hasBytesAvailable]) {
                    len = [inputStream read:buffer maxLength:sizeof(buffer)];
                    if (len > 0) {
                        
                        NSString *output = [[NSString alloc] initWithBytes:buffer length:len encoding:NSASCIIStringEncoding];
                        
                        if (nil != output) {
                            [self messageReceived:output];
                        }
                    }
                }
            }
            break;
        
        // could not connect!
		case NSStreamEventErrorOccurred:
			NSLog(@"Can not connect to the host!");
            startCount++;
            showAlert = TRUE;
			break;
        
        // disconnected, close streams, push EchoView to the back
		case NSStreamEventEndEncountered:
            [theStream close];
            [theStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
            [self.view sendSubviewToBack:_EchoView];
			break;
            
		default:
			NSLog(@"Unknown event");
            break;
	}
    
    // create modal window when connection fails
    if(showAlert) {
        if(startCount % 2 == 0) {
            UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Unable to Connect to JPServer!"
                                                            message:@"Are You Running JPClient with the Correct IP and Port?"
                                                           delegate:self
                                                  cancelButtonTitle:@"Dismiss"
                                                  otherButtonTitles:nil,nil];
            [alert show];
            showAlert = FALSE;
        }
    }
}

- (void) messageReceived:(NSString *)message {
    
    // push received message into array
	[commands addObject:message];
    
    // refresh table
	[_CommandTableView reloadData];
    
    // set scroll value
    NSIndexPath *scrollIndexPath = [NSIndexPath indexPathForRow:([commands count] - 1) inSection:0];
    [_CommandTableView scrollToRowAtIndexPath:scrollIndexPath atScrollPosition:UITableViewScrollPositionBottom animated:YES];
}

- (IBAction)PressConnect:(id)sender {
    
    //[self initNetworkCommunication:@"146.229.232.247" port:@"11865"];
    [self initNetworkCommunication:_IPTextField.text port:_PortTextField.text];
    
}

- (IBAction)PressSend:(id)sender {
    
    // set message
    NSString *response = [NSString stringWithFormat:@"%@ \n", _CommandTextField.text];
  
    // send non-empty message
    if(![response isEqualToString:@""]) {
        NSData *data = [[NSData alloc] initWithData:[response dataUsingEncoding:NSASCIIStringEncoding]];
        [outputStream write:[data bytes] maxLength:1024];
    }
    
    // reset command text field
    _CommandTextField.text = @"";
    
}

@end
