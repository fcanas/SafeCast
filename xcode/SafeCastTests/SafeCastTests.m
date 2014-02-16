//
//  SafeCastTests.m
//  SafeCastTests
//
//  Created by Fabian Canas on 2/13/14.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Fabian Canas
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to
//  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//  the Software, and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#import <XCTest/XCTest.h>
#import <SafeCast/SafeCast.h>

@interface SafeCastTests : XCTestCase {
    NSString *s;
    NSArray *a;
    NSMutableArray *ma;
}
@end

@implementation SafeCastTests

- (void)setUp
{
    [super setUp];
    s = @"string";
    a = [NSMutableArray array];
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testCast
{
    ma = [NSMutableArray cast:a];
    
    XCTAssertEqual(ma, a, @"Should successfully cast a (mutable) array to a mutable array");
    XCTAssertNil([NSMutableArray cast:s], @"Should not cast a string to a mutable array");
    XCTAssertNil([NSMutableArray cast:[NSArray array]], @"Should not cast an array to a mutable array");
}

- (void)testCastIntoBlock
{
    void(^addObjectBlock)(NSMutableArray *) = ^(NSMutableArray *array){
        [array addObject:s];
    };
    
    ma = [NSMutableArray cast:a intoBlock:addObjectBlock];
    
    XCTAssertEqual(ma, a, @"Should successfully cast a (mutable) array to a mutable array");
    XCTAssertEqual(a.firstObject, s, @"Should successfully execute the block passed to a cast mutable array.");
    
    XCTAssertNil([NSMutableArray cast:s], @"Should not cast a string to a mutable array");
    XCTAssertNil([NSMutableArray cast:[NSArray array]], @"Should not cast an array to a mutable array");
}

@end
