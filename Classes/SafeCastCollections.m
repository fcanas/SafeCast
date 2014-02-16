//
//  SafeCastCollections.m
//  Pods
//
//  Created by Fabian Canas on 2/15/14.
//
//

#import "SafeCastCollections.h"

@implementation NSArray (SafeCast)

#ifdef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#undef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#endif
#define SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE (id obj, NSUInteger idx, BOOL *stop)

#ifdef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#undef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#endif
#define SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS obj,idx,stop

#include "SafeCastPerformSelector.h"
#include "SafeCastEnumeration.h"
#include "SafeCastIndexedEnumeration.h"

@end

@implementation NSOrderedSet (SafeCast)

#ifdef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#undef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#endif
#define SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE (id obj, NSUInteger idx, BOOL *stop)

#ifdef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#undef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#endif
#define SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS obj,idx,stop

#include "SafeCastEnumeration.h"
#include "SafeCastIndexedEnumeration.h"

@end

@implementation NSSet (SafeCast)

#ifdef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#undef SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE
#endif
#define SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE (id obj, BOOL *stop)

#ifdef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#undef SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS
#endif
#define SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS obj,stop

#include "SafeCastPerformSelector.h"
#include "SafeCastEnumeration.h"

@end
