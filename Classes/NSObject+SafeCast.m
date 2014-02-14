//
//  NSObject+SafeCast.m
//  Pods
//
//  Created by Fabian Canas on 2/13/14.
//
//

#import "NSObject+SafeCast.h"

@implementation NSObject (SafeCast)

+ (instancetype)cast:(id)x
{
    if ([x isKindOfClass:self]) {
        return x;
    }
    return nil;
}

@end
