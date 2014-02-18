//
//  SafeCastCollections.m
//  Pods
//
//  Created by Fabian Canas on 2/15/14.
//
//

#import "SafeCastCollections.h"

@implementation NSArray (SafeCast)

#undef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#define SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE (id obj, NSUInteger idx, BOOL *stop)

#undef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#define SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS obj,idx,stop

#include "SafeCastPerformSelector.h"
#include "SafeCastEnumeration.h"
#include "SafeCastIndexedEnumeration.h"

@end

@implementation NSOrderedSet (SafeCast)

#include "SafeCastEnumeration.h"
#include "SafeCastIndexedEnumeration.h"

@end

@implementation NSSet (SafeCast)

#undef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#define SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE (id obj, BOOL *stop)

#undef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#define SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS obj,stop

#include "SafeCastPerformSelector.h"
#include "SafeCastEnumeration.h"

@end

@implementation NSDictionary (SafeCast)

#define SAFE_CAST_KEYED_ENUMERATION 1

#undef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#define SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE (id key, id obj, BOOL *stop)

#undef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#define SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS key,obj,stop

#include "SafeCastEnumeration.h"

@end
