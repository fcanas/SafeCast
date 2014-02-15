//
//  FFCCollectionTest.m
//  SafeCast
//
//  Created by Fabian Canas on 2/15/14.
//  Copyright (c) 2014 Fabián Cañas. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <SafeCast/NSObject+SafeCast.h>
#import <SafeCast/SafeCastCollections.h>

#pragma mark - Test Classes

@protocol FFCTestProtocol <NSObject>
@required
@property (nonatomic, strong) NSNumber *number;
@property (nonatomic, assign) BOOL methodCalled;
- (void)method;
@end

@interface FFCTestObject : NSObject
@property (nonatomic, strong) NSNumber *number;
@property (nonatomic, assign) BOOL methodCalled;
- (void)method;
@end

@implementation FFCTestObject
- (void)method { self.methodCalled = YES; }
@end

@interface FFCProtocolTestObject : FFCTestObject<FFCTestProtocol>
@end
@implementation FFCProtocolTestObject
@end

@interface FFCCollectionTest : XCTestCase

@end

#pragma mark - Tests

@implementation FFCCollectionTest

- (void)setUp
{
    [super setUp];
    // Put setup code here; it will be run once, before the first test case.
}

- (void)tearDown
{
    // Put teardown code here; it will be run once, after the last test case.
    [super tearDown];
}

#pragma mark - Responds to Selector

- (void)testMakeObjectSafelyPerformSelector
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    
    XCTAssertNoThrow([a makeObjectsSafelyPerformSelector:@selector(method)], @"Objects that do not implement `-method` should not raise");
    XCTAssertTrue([FFCTestObject cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

- (void)testMakeObjectSafelyPerformSelectorWithObject
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    
    XCTAssertNoThrow([a makeObjectsSafelyPerformSelector:@selector(setNumber:) withObject:@3], @"Objects that do not implement `-setNumber` should not raise");
    XCTAssertEqualObjects([FFCTestObject cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertEqualObjects([FFCTestObject cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

#pragma mark - Kind of Class

- (void)testEnumerateObjectsOfKindUsingBlock
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    
    XCTAssertNoThrow([a enumerateObjectsOfKind:[FFCTestObject class]
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertEqualObjects([FFCTestObject cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumeration
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    
    XCTAssertNoThrow([a enumerateObjectsOfKind:[FFCTestObject class]
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                        *stop = YES;
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject cast:a[3]].number, @"objects should not be enumerated after a block indicated enumaration should stop");

}

- (void)testEnumerateObjectsOfKindAtIndexesOptionsUsingBlock
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    
    XCTAssertNoThrow([a enumerateObjectsOfKind:[FFCTestObject class]
                                     AtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                       options:kNilOptions
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject cast:a[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

#pragma mark - Conforms to Protocol

- (void)testEnumerateObjectsConformingToProtocolUsingBlock
{
    NSArray *a = @[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]];
    
    XCTAssertNoThrow([a enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject cast:a[0]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject cast:a[2]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumerationConformingToProtocol
{
    NSArray *a = @[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]];
    
    XCTAssertNoThrow([a enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                        *stop = YES;
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject cast:a[3]].number, @"objects should not be enumerated after a block indicated enumaration should stop");
    
}

- (void)testEnumerateConformingToProtocolAtIndexesOptionsUsingBlock
{
    NSArray *a = @[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]];
    
    XCTAssertNoThrow([a enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                     AtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                       options:kNilOptions
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject cast:a[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertNil([FFCTestObject cast:a[2]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

@end
