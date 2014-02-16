//
//  SafeCastCollections.m
//  Pods
//
//  Created by Fabian Canas on 2/15/14.
//
//

#import "SafeCastCollections.h"

@implementation NSArray (SafeCast)

#pragma mark - Responds to Selector

- (void)makeObjectsSafelyPerformSelector:(SEL)aSelector;
{
    if (aSelector == NULL) {
        [[[NSException alloc] initWithName:NSInvalidArgumentException reason:@"A selector passed to -makeObjectsSafelyPerformSelector: must not be nil" userInfo:nil] raise];
    }
    
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj respondsToSelector:aSelector]) {
            [obj performSelector:aSelector];
        }
    }];
}

- (void)makeObjectsSafelyPerformSelector:(SEL)aSelector withObject:(id)anObject
{
    if (aSelector == NULL) {
        [[[NSException alloc] initWithName:NSInvalidArgumentException reason:@"A selector passed to -makeObjectsSafelyPerformSelector:withObject: must not be nil" userInfo:nil] raise];
    }
    
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj respondsToSelector:aSelector]) {
            [obj performSelector:aSelector withObject:anObject];
        }
    }];
}

#include "SafeCastIndexedEnumeration.h"

@end

@implementation NSOrderedSet (SafeCast)
    
#include "SafeCastIndexedEnumeration.h"

@end
