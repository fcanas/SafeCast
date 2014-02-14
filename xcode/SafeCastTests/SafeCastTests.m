//
//  SafeCastTests.m
//  SafeCastTests
//
//  Created by Fabian Canas on 2/13/14.
//  Copyright (c) 2014 Fabián Cañas. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <SafeCast/NSObject+SafeCast.h>

@interface SafeCastTests : XCTestCase

@end

@implementation SafeCastTests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testCast
{
    NSString *s = @"string";
    NSArray *a = [NSMutableArray array];
    NSMutableArray *ma = [NSMutableArray cast:a];
    
    XCTAssertEqual(ma, a, @"Should successfully cast a (mutable) array to a mutable array");
    XCTAssertNil([NSMutableArray cast:s], @"Should not cast a string to a mutable array");
    XCTAssertNil([NSMutableArray cast:[NSArray array]], @"Should not cast an array to a mutable array");
}

@end
