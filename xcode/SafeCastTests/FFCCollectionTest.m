//
//  FFCCollectionTest.m
//  SafeCast
//
//  Created by Fabian Canas on 2/15/14.
//  Copyright (c) 2014 Fabián Cañas. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <SafeCast/SafeCast.h>

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

@interface FFCArrayTest : XCTestCase
@end

@interface FFCOrderedSetTest : XCTestCase
@end

@interface FFCSetTest : XCTestCase
@end

@interface FFCDictionaryTest : XCTestCase
@end

#pragma mark - NSArray Tests

@implementation FFCArrayTest

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
    
    XCTAssertNoThrow([a safe_makeObjectsSafelyPerformSelector:@selector(method)], @"Objects that do not implement `-method` should not raise");
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

- (void)testMakeObjectSafelyPerformSelectorWithObject
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    
    XCTAssertNoThrow([a safe_makeObjectsSafelyPerformSelector:@selector(setNumber:) withObject:@3], @"Objects that do not implement `-setNumber` should not raise");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testRespondsToSelector
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    
    
    XCTAssertNoThrow([a safe_enumerateObjectsRespondingToSelector:@selector(method) usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

- (void)testRespondsToSelectorWithOptions
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    
    
    XCTAssertNoThrow([a safe_enumerateObjectsRespondingToSelector:@selector(method) withOptions:kNilOptions usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

- (void)testRespondsToSelectorAtIndicesWithOptions
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    NSIndexSet *i = [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, 2)];
    
    XCTAssertNoThrow([a safe_enumerateObjectsRespondingToSelector:@selector(method) atIndexes:i options:kNilOptions usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertFalse([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

#pragma mark - Kind of Class

- (void)testEnumerateObjectsOfKindUsingBlock
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCProtocolTestObject new]];
    
    XCTAssertNoThrow([a safe_enumerateObjectsOfKind:[FFCTestObject class]
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumeration
{
    NSArray *a = @[[NSObject new], [FFCProtocolTestObject new], [NSObject new], [FFCTestObject new]];
    
    XCTAssertNoThrow([a safe_enumerateObjectsOfKind:[FFCTestObject class]
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                        *stop = YES;
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject safe_cast:a[3]].number, @"objects should not be enumerated after a block indicated enumaration should stop");
}

- (void)testEnumerateObjectsOfKindAtIndexesOptionsUsingBlock
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCProtocolTestObject new]];
    
    XCTAssertNoThrow([a safe_enumerateObjectsOfKind:[FFCTestObject class]
                                     atIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                       options:kNilOptions
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject safe_cast:a[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testEnumerateObjectsOfKindAtIndexesOptionsUsingBlock_legacy
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCProtocolTestObject new]];
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    XCTAssertNoThrow([a safe_enumerateObjectsOfKind:[FFCTestObject class]
                                          AtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                            options:kNilOptions
                                         usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                             [obj setNumber:@3];
                                         }], @"Objects that do not implement `-setNumber` should not raise");
    #pragma clang diagnostic pop
    
    XCTAssertNil([FFCTestObject safe_cast:a[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testIndexesOfObjectsOfKind
{
    NSArray *a = @[[NSObject new], [NSObject new], [FFCTestObject new], [FFCProtocolTestObject new]];
    NSIndexSet *indexSet = [a safe_indexesOfObjectsOfKind:[FFCTestObject class]];
    
    XCTAssertEqualObjects(indexSet, [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)], @"should return an index set corresponding to the objects of kind");
}

#pragma mark - Conforms to Protocol

- (void)testEnumerateObjectsConformingToProtocolUsingBlock
{
    NSArray *a = @[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]];
    
    XCTAssertNoThrow([a safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject safe_cast:a[0]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject safe_cast:a[2]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumerationConformingToProtocol
{
    NSArray *a = @[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]];
    
    XCTAssertNoThrow([a safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                        *stop = YES;
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject safe_cast:a[3]].number, @"objects should not be enumerated after a block indicated enumaration should stop");
    
}

- (void)testEnumerateConformingToProtocolAtIndexesOptionsUsingBlock
{
    NSArray *a = @[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]];
    
    XCTAssertNoThrow([a safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                     atIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                       options:kNilOptions
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject safe_cast:a[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertNil([FFCTestObject safe_cast:a[2]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testEnumerateConformingToProtocolAtIndexesOptionsUsingBlock_legacy
{
    NSArray *a = @[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]];
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    XCTAssertNoThrow([a safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                        AtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                                          options:kNilOptions
                                                       usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                                           [obj setNumber:@3];
                                                       }], @"Objects that do not implement `-setNumber` should not raise");
    #pragma clang diagnostic pop
    XCTAssertNil([FFCTestObject safe_cast:a[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertNil([FFCTestObject safe_cast:a[2]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:a[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testIndexesOfObjectsConformingToProtocol
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [FFCProtocolTestObject new], [FFCProtocolTestObject new], @3, @4];
    NSIndexSet *indexSet = [a safe_indexesOfObjectsConformingToProtocol:@protocol(FFCTestProtocol)];
    
    XCTAssertEqualObjects(indexSet, [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)], @"should return an index set corresponding to the objects of kind");
}

@end

#pragma mark - NSOrderedSet Tests

@implementation FFCOrderedSetTest

#pragma mark - Responds to Selector

- (void)testRespondsToSelector
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    NSOrderedSet *s= [NSOrderedSet orderedSetWithArray:a];
    
    XCTAssertNoThrow([s safe_enumerateObjectsRespondingToSelector:@selector(method) usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

- (void)testRespondsToSelectorWithOptions
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    NSOrderedSet *s= [NSOrderedSet orderedSetWithArray:a];
    
    XCTAssertNoThrow([s safe_enumerateObjectsRespondingToSelector:@selector(method) withOptions:kNilOptions usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

- (void)testRespondsToSelectorAtIndicesWithOptions
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    NSIndexSet *i = [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, 2)];
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:a];
    
    XCTAssertNoThrow([s safe_enumerateObjectsRespondingToSelector:@selector(method) atIndexes:i options:kNilOptions usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertFalse([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

#pragma mark - Kind of Class

- (void)testEnumerateObjectsOfKindUsingBlock
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[@1, [FFCTestObject new], @2, [FFCProtocolTestObject new]]];
    
    XCTAssertNoThrow([s safe_enumerateObjectsOfKind:[FFCTestObject class]
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumeration
{
        NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[@1, [FFCTestObject new], @2, [FFCProtocolTestObject new]]];
    
    XCTAssertNoThrow([s safe_enumerateObjectsOfKind:[FFCTestObject class]
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                        *stop = YES;
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject safe_cast:s[3]].number, @"objects should not be enumerated after a block indicated enumaration should stop");
}

- (void)testEnumerateObjectsOfKindAtIndexesOptionsUsingBlock
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[@1, [FFCTestObject new], @2, [FFCProtocolTestObject new]]];
    
    XCTAssertNoThrow([s safe_enumerateObjectsOfKind:[FFCTestObject class]
                                          atIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                            options:kNilOptions
                                         usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                             [obj setNumber:@3];
                                         }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject safe_cast:s[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testEnumerateObjectsOfKindAtIndexesOptionsUsingBlock_legacy
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[@1, [FFCTestObject new], @2, [FFCProtocolTestObject new]]];
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    XCTAssertNoThrow([s safe_enumerateObjectsOfKind:[FFCTestObject class]
                                     AtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                       options:kNilOptions
                                    usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    #pragma clang diagnostic pop
    XCTAssertNil([FFCTestObject safe_cast:s[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testIndexesOfObjectsOfKind
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[@1, @2, [FFCTestObject new], [FFCProtocolTestObject new]]];
    NSIndexSet *indexSet = [s safe_indexesOfObjectsOfKind:[FFCTestObject class]];
    
    XCTAssertEqualObjects(indexSet, [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)], @"should return an index set corresponding to the objects of kind");
}

#pragma mark - Conforms to Protocol

- (void)testEnumerateObjectsConformingToProtocolUsingBlock
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]]];
    
    XCTAssertNoThrow([s safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                  usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                                      [obj setNumber:@3];
                                                  }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject safe_cast:s[0]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject safe_cast:s[2]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumerationConformingToProtocol
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]]];
    
    XCTAssertNoThrow([s safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                  usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                                      [obj setNumber:@3];
                                                      *stop = YES;
                                                  }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[1]].number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil([FFCTestObject safe_cast:s[3]].number, @"objects should not be enumerated after a block indicated enumaration should stop");
    
}

- (void)testEnumerateConformingToProtocolAtIndexesOptionsUsingBlock
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]]];
    
    XCTAssertNoThrow([s safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                        atIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                                          options:kNilOptions
                                                       usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                                           [obj setNumber:@3];
                                                       }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil([FFCTestObject safe_cast:s[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertNil([FFCTestObject safe_cast:s[2]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testEnumerateConformingToProtocolAtIndexesOptionsUsingBlock_legacy
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[[FFCTestObject new], [FFCProtocolTestObject new], [FFCTestObject new], [FFCProtocolTestObject new]]];
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    XCTAssertNoThrow([s safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                   AtIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)]
                                                     options:kNilOptions
                                                  usingBlock:^(FFCTestObject *obj, NSUInteger idx, BOOL *stop) {
                                                      [obj setNumber:@3];
                                                  }], @"Objects that do not implement `-setNumber` should not raise");
    #pragma clang diagnostic pop
    XCTAssertNil([FFCTestObject safe_cast:s[1]].number, @"known objects not included in the index set should not have had methods called on it");
    XCTAssertNil([FFCTestObject safe_cast:s[2]].number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects([FFCTestObject safe_cast:s[3]].number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testIndexesOfObjectsConformingToProtocol
{
    NSOrderedSet *s = [NSOrderedSet orderedSetWithArray:@[[NSObject new], [FFCTestObject new], [FFCProtocolTestObject new], [FFCProtocolTestObject new], @3, @4]];
    NSIndexSet *indexSet = [s safe_indexesOfObjectsConformingToProtocol:@protocol(FFCTestProtocol)];
    
    XCTAssertEqualObjects(indexSet, [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(2, 2)], @"should return an index set corresponding to the objects of kind");
}

@end

#pragma mark - NSSet Tests

@implementation FFCSetTest

#pragma mark - Responds to Selector

- (void)testMakeObjectSafelyPerformSelector
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    NSSet *s = [NSSet setWithArray:@[@1, obj1, @2, obj2]];
    
    XCTAssertNoThrow([s safe_makeObjectsSafelyPerformSelector:@selector(method)], @"Objects that do not implement `-method` should not raise");
    XCTAssertTrue(obj1.methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue(obj2.methodCalled, @"known objects should have had methods called on it");
}

- (void)testMakeObjectSafelyPerformSelectorWithObject
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    NSSet *s = [NSSet setWithArray:@[@1, obj1, @2, obj2]];
    
    XCTAssertNoThrow([s safe_makeObjectsSafelyPerformSelector:@selector(setNumber:) withObject:@3], @"Objects that do not implement `-setNumber:` should not raise");
    XCTAssertEqualObjects(obj1.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertEqualObjects(obj2.number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testRespondsToSelector
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    NSSet *s= [NSSet setWithArray:a];
    
    XCTAssertNoThrow([s safe_enumerateObjectsRespondingToSelector:@selector(method) usingBlock:^(id obj, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

- (void)testRespondsToSelectorWithOptions
{
    NSArray *a = @[[NSObject new], [FFCTestObject new], [NSObject new], [FFCTestObject new]];
    NSSet *s= [NSSet setWithArray:a];
    
    XCTAssertNoThrow([s safe_enumerateObjectsRespondingToSelector:@selector(method) withOptions:kNilOptions usingBlock:^(id obj, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:a[1]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:a[3]].methodCalled, @"known objects should have had methods called on it");
}

#pragma mark - Kind of Class

- (void)testEnumerateObjectsOfKindUsingBlock
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    NSSet *s = [NSSet setWithArray:@[@1, obj1, @2, obj2]];
    
    XCTAssertNoThrow([s safe_enumerateObjectsOfKind:[FFCTestObject class]
                                    usingBlock:^(FFCTestObject *obj, BOOL *stop) {
                                        [obj setNumber:@3];
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertEqualObjects(obj1.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertEqualObjects(obj2.number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumeration
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    NSSet *s = [NSSet setWithArray:@[@1, obj1, @2, obj2]];
    
    FFCTestObject __block *testedObject;
    
    XCTAssertNoThrow([s safe_enumerateObjectsOfKind:[FFCTestObject class]
                                    usingBlock:^(FFCTestObject *obj, BOOL *stop) {
                                        [obj setNumber:@3];
                                        testedObject = obj;
                                        *stop = YES;
                                    }], @"Objects that do not implement `-setNumber` should not raise");
    
    FFCTestObject *untestedObject = testedObject==obj1?obj2:obj1;
    
    XCTAssertEqualObjects(testedObject.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil(untestedObject.number, @"objects should not be enumerated after a block indicated enumaration should stop");
}

#pragma mark - Conforms to Protocol

- (void)testEnumerateObjectsConformingToProtocolUsingBlock
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    FFCTestObject *obj3 = [FFCTestObject new];
    FFCProtocolTestObject *obj4 = [FFCProtocolTestObject new];

    NSSet *s = [NSSet setWithArray:@[obj1, obj2, obj3, obj4]];
    
    XCTAssertNoThrow([s safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                  usingBlock:^(FFCTestObject *obj, BOOL *stop) {
                                                      [obj setNumber:@3];
                                                  }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil(obj1.number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects(obj2.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil(obj3.number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects(obj4.number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumerationConformingToProtocol
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    FFCTestObject *obj3 = [FFCTestObject new];
    FFCProtocolTestObject *obj4 = [FFCProtocolTestObject new];
    
    NSSet *s = [NSSet setWithArray:@[obj1, obj2, obj3, obj4]];
    
    FFCTestObject __block *testedObject;
    
    XCTAssertNoThrow([s safe_enumerateObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                  usingBlock:^(FFCTestObject *obj, BOOL *stop) {
                                                      [obj setNumber:@3];
                                                      *stop = YES;
                                                      testedObject = obj;
                                                  }], @"Objects that do not implement `-setNumber` should not raise");
    
    FFCTestObject *untestedObject = testedObject==obj2?obj4:obj2;
    
    XCTAssertEqualObjects(testedObject.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil(untestedObject.number, @"objects should not be enumerated after a block indicated enumaration should stop");
}

@end

#pragma mark - NSDictionary

@implementation FFCDictionaryTest

- (void)testEnumerateObjectsOfKindUsingBlock
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    FFCTestObject *obj3 = [FFCTestObject new];
    FFCProtocolTestObject *obj4 = [FFCProtocolTestObject new];
    
    NSDictionary *d = @{@1:obj1, @2:obj2, @3:obj3, @4:obj4};
    
    
    XCTAssertNoThrow([d safe_enumerateKeysAndObjectsOfKind:[FFCProtocolTestObject class]
                                                         usingBlock:^(id key, FFCTestObject *obj, BOOL *stop) {
                                                             [obj setNumber:@3];
                                                         }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil(obj1.number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects(obj2.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil(obj3.number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects(obj4.number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumerationOfKind
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    FFCTestObject *obj3 = [FFCTestObject new];
    FFCProtocolTestObject *obj4 = [FFCProtocolTestObject new];
    
    NSDictionary *d = @{@1:obj1, @2:obj2, @3:obj3, @4:obj4};
    
    FFCTestObject __block *testedObject;
    
    XCTAssertNoThrow([d safe_enumerateKeysAndObjectsOfKind:[FFCProtocolTestObject class]
                                                  usingBlock:^(id key, FFCTestObject *obj, BOOL *stop) {
                                                      [obj setNumber:@3];
                                                      *stop = YES;
                                                      testedObject = obj;
                                                  }], @"Objects that do not implement `-setNumber` should not raise");
    
    FFCTestObject *untestedObject = testedObject==obj2?obj4:obj2;
    
    XCTAssertEqualObjects(testedObject.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil(untestedObject.number, @"objects should not be enumerated after a block indicated enumaration should stop");
}


#pragma mark - Conforms to Protocol

- (void)testEnumerateObjectsConformingToProtocolUsingBlock
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    FFCTestObject *obj3 = [FFCTestObject new];
    FFCProtocolTestObject *obj4 = [FFCProtocolTestObject new];
    
    NSDictionary *d = @{@1:obj1, @2:obj2, @3:obj3, @4:obj4};
    
    
    XCTAssertNoThrow([d safe_enumerateKeysAndObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                  usingBlock:^(id key, FFCTestObject *obj, BOOL *stop) {
                                                      [obj setNumber:@3];
                                                  }], @"Objects that do not implement `-setNumber` should not raise");
    
    XCTAssertNil(obj1.number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects(obj2.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil(obj3.number, @"objects not conforming to the protocol should not have had methods called on it");
    XCTAssertEqualObjects(obj4.number, @3, @"known objects should have had methods called on it with correct object");
}

- (void)testStoppingBlockEnumerationConformingToProtocol
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    FFCTestObject *obj3 = [FFCTestObject new];
    FFCProtocolTestObject *obj4 = [FFCProtocolTestObject new];
    
    NSDictionary *d = @{@1:obj1, @2:obj2, @3:obj3, @4:obj4};
    
    FFCTestObject __block *testedObject;
    
    XCTAssertNoThrow([d safe_enumerateKeysAndObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                           usingBlock:^(id key, FFCTestObject *obj, BOOL *stop) {
                                               [obj setNumber:@3];
                                               *stop = YES;
                                               testedObject = obj;
                                           }], @"Objects that do not implement `-setNumber` should not raise");
    
    FFCTestObject *untestedObject = testedObject==obj2?obj4:obj2;
    
    XCTAssertEqualObjects(testedObject.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil(untestedObject.number, @"objects should not be enumerated after a block indicated enumaration should stop");
}

- (void)testStoppingBlockEnumerationConformingToProtocolWithOptions
{
    FFCTestObject *obj1 = [FFCTestObject new];
    FFCProtocolTestObject *obj2 = [FFCProtocolTestObject new];
    FFCTestObject *obj3 = [FFCTestObject new];
    FFCProtocolTestObject *obj4 = [FFCProtocolTestObject new];
    
    NSDictionary *d = @{@1:obj1, @2:obj2, @3:obj3, @4:obj4};
    
    FFCTestObject __block *testedObject;
    
    XCTAssertNoThrow([d safe_enumerateKeysAndObjectsConformingToProtocol:@protocol(FFCTestProtocol)
                                                        withOptions:kNilOptions
                                                         usingBlock:^(id key, FFCTestObject *obj, BOOL *stop) {
                                                             [obj setNumber:@3];
                                                             *stop = YES;
                                                             testedObject = obj;
                                                         }], @"Objects that do not implement `-setNumber` should not raise");
    
    FFCTestObject *untestedObject = testedObject==obj2?obj4:obj2;
    
    XCTAssertEqualObjects(testedObject.number, @3, @"known objects should have had methods called on it with correct object");
    XCTAssertNil(untestedObject.number, @"objects should not be enumerated after a block indicated enumaration should stop");
}

#pragma mark - Responds to Selector

- (void)testRespondsToSelector
{
    NSDictionary *d = @{@1:[NSObject new], @2:[FFCTestObject new], @3:[NSObject new], @4:[FFCTestObject new]};
    
    XCTAssertNoThrow([d safe_enumerateKeysAndObjectsRespondingToSelector:@selector(method) usingBlock:^(id key, FFCTestObject *obj, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:d[@2]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:d[@4]].methodCalled, @"known objects should have had methods called on it");
}

- (void)testRespondsToSelectorWithOptions
{
    NSDictionary *d = @{@1:[NSObject new], @2:[FFCTestObject new], @3:[NSObject new], @4:[FFCTestObject new]};
    
    XCTAssertNoThrow([d safe_enumerateKeysAndObjectsRespondingToSelector:@selector(method) withOptions:kNilOptions usingBlock:^(id key, FFCTestObject *obj, BOOL *stop) {
        [obj method];
    }], @"Should be able to enumerate objects responding to selector without raising.");
    
    XCTAssertTrue([FFCTestObject safe_cast:d[@2]].methodCalled, @"known objects should have had methods called on it");
    XCTAssertTrue([FFCTestObject safe_cast:d[@4]].methodCalled, @"known objects should have had methods called on it");
}

@end
