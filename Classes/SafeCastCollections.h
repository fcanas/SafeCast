//
//  SafeCastCollections.h
//  Pods
//
//  Created by Fabian Canas on 2/15/14.
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

#import <Foundation/Foundation.h>

@interface NSArray (SafeCast)

#pragma mark - Responds to Selector

/**
 Sends to each object in the array the message identified by a given selector, starting with the first object and continuing through the array to the last object if and only if the object responds to the given selector.

 This method raises an NSInvalidArgumentException if aSelector is NULL.
 
 @param aSelector A selector that identifies the message to send to the objects in the array. The method must not take any arguments, and must not have the side effect of modifying the receiving array.
 
 Availability
 Available in iOS 2.0 and later.
 
 @see - makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)makeObjectsSafelyPerformSelector:(SEL)aSelector;

/**
 Sends the aSelector message to each object in the array, starting with the first object and continuing through the array to the last object if and only if the object responds to the given selector.

 This method raises an NSInvalidArgumentException if aSelector is NULL.
 
 @param aSelector A selector that identifies the message to send to the objects in the array. The method must take a single argument of type id, and must not have the side effect of modifying the receiving array.
 
 @param anObject The object to send as the argument to each invocation of the aSelector method.

 @see - makeObjectsPerformSelectorSafely:
 @see – makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)makeObjectsSafelyPerformSelector:(SEL)aSelector withObject:(id)anObject;

#pragma mark - Kind of Class NSArray

/**
 Executes a given block using each object in the array matching the indicated Class, starting with the first object and continuing through the array to the last object.

 If the Block parameter is nil this method will raise an exception.

 This method executes synchronously.

 @param class 
    The Class objects in the array must be a kind of for the block to be executed on
 @param block
    The block to apply to elements in the array.
    The block takes three arguments:
    obj
        The element in the array.
    idx
        The index of the element in the array.
    stop
        A reference to a Boolean value. The block can set the value to YES to stop further processing of the array. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 @see – enumerateObjectsWithOptions:usingBlock:
 @see – makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsOfKind:(Class)class usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using each object in the array.

 @param class
 The Class objects in the array must be a kind of for the block to be executed on
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @param block
 The block to apply to elements in the array.
 The block takes three arguments:
 obj
 The element in the array.
 idx
 The index of the element in the array.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the array. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.

 By default, the enumeration starts with the first object and continues serially through the array to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsOfKind:(Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using the objects in the array at the specified indexes.
 
 @param class
 The Class objects in the array must be a kind of for the block to be executed on
 @param indexSet
 The indexes of the objects over which to enumerate.
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @block block
 The block to apply to elements in the array.
 The block takes three arguments:
 obj
 The element in the array.
 idx
 The index of the element in the array.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the array. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.

 By default, the enumeration starts with the first object and continues serially through the array to the last element specified by indexSet. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsOfKind:(Class)class AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Returns the indexes of objects in the array that are of the kind of the given Class.
 
 @param class
 The Class objects in the array must be a kind of for their index to be returned in the index set
 
 @return
 The indexes whose corresponding values in the array are the kind of object class passed. If no objects in the array pass the test, returns an empty index set.
 */
- (NSIndexSet *)indexesOfObjectsOfKind:(Class)class;

#pragma mark - Conforms to Protocol - Array

/**
 Executes a given block using each object in the array matching the indicated Class, starting with the first object and continuing through the array to the last object.
 
 If the Block parameter is nil this method will raise an exception.
 
 This method executes synchronously.
 
 @param protocol
 The Protocol objects in the array must be a kind of for the block to be executed on
 @param block
 The block to apply to elements in the array.
 The block takes three arguments:
 obj
 The element in the array.
 idx
 The index of the element in the array.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the array. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 @see – enumerateObjectsWithOptions:usingBlock:
 @see – makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using each object in the array.
 
 @param protocol
 The Protocol objects in the array must be a kind of for the block to be executed on
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @param block
 The block to apply to elements in the array.
 The block takes three arguments:
 obj
 The element in the array.
 idx
 The index of the element in the array.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the array. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 By default, the enumeration starts with the first object and continues serially through the array to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using the objects in the array at the specified indexes.
 
 @param protocol
 The Protocol objects in the array must be a kind of for the block to be executed on
 @param indexSet
 The indexes of the objects over which to enumerate.
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @block block
 The block to apply to elements in the array.
 The block takes three arguments:
 obj
 The element in the array.
 idx
 The index of the element in the array.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the array. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 By default, the enumeration starts with the first object and continues serially through the array to the last element specified by indexSet. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Returns the indexes of objects in the array that conform to the given protocol.
 
 @param protocol
 The Protocol which objects in the array must conform to for their index to be returned in the index set
 
 @return
 The indexes whose corresponding values in the array are the kind of object class passed. If no objects in the array pass the test, returns an empty index set.
 */
- (NSIndexSet *)indexesOfObjectsConformingToProtocol:(Protocol *)protocol;

@end

#pragma mark -

@interface NSOrderedSet (SafeCast)

/**
 Executes a given block using each object in the ordered set matching the indicated Class, starting with the first object and continuing through the ordered set to the last object.
 
 If the Block parameter is nil this method will raise an exception.
 
 This method executes synchronously.
 
 @param class
 The Class objects in the ordered set must be a kind of for the block to be executed on
 @param block
 The block to apply to elements in the ordered set.
 The block takes three arguments:
 obj
 The element in the ordered set.
 idx
 The index of the element in the ordered set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the ordered set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 @see – enumerateObjectsWithOptions:usingBlock:
 @see – makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsOfKind:(Class)class usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using each object in the ordered set.
 
 @param class
 The Class objects in the ordered set must be a kind of for the block to be executed on
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @param block
 The block to apply to elements in the ordered set.
 The block takes three arguments:
 obj
 The element in the ordered set.
 idx
 The index of the element in the ordered set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the ordered set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 By default, the enumeration starts with the first object and continues serially through the ordered set to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsOfKind:(Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using the objects in the ordered set at the specified indexes.
 
 @param class
 The Class objects in the ordered set must be a kind of for the block to be executed on
 @param indexSet
 The indexes of the objects over which to enumerate.
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @block block
 The block to apply to elements in the ordered set.
 The block takes three arguments:
 obj
 The element in the ordered set.
 idx
 The index of the element in the ordered set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the ordered set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 By default, the enumeration starts with the first object and continues serially through the ordered set to the last element specified by indexSet. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsOfKind:(Class)class AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Returns the indexes of objects in the ordered set that are of the kind of the given Class.
 
 @param class
 The Class objects in the ordered set must be a kind of for their index to be returned in the index set
 
 @return
 The indexes whose corresponding values in the ordered set are the kind of object class passed. If no objects in the ordered set pass the test, returns an empty index set.
 */
- (NSIndexSet *)indexesOfObjectsOfKind:(Class)class;

#pragma mark - Protocols NSOrderedSet

/**
 Executes a given block using each object in the ordered set matching the indicated Class, starting with the first object and continuing through the ordered set to the last object.
 
 If the Block parameter is nil this method will raise an exception.
 
 This method executes synchronously.
 
 @param protocol
 The Protocol objects in the ordered set must be a kind of for the block to be executed on
 @param block
 The block to apply to elements in the ordered set.
 The block takes three arguments:
 obj
 The element in the ordered set.
 idx
 The index of the element in the ordered set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the ordered set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 @see – enumerateObjectsWithOptions:usingBlock:
 @see – makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using each object in the ordered set.
 
 @param protocol
 The Protocol objects in the ordered set must be a kind of for the block to be executed on
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @param block
 The block to apply to elements in the ordered set.
 The block takes three arguments:
 obj
 The element in the ordered set.
 idx
 The index of the element in the ordered set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the ordered set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 By default, the enumeration starts with the first object and continues serially through the ordered set to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using the objects in the ordered set at the specified indexes.
 
 @param protocol
 The Protocol objects in the ordered set must be a kind of for the block to be executed on
 @param indexSet
 The indexes of the objects over which to enumerate.
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @block block
 The block to apply to elements in the ordered set.
 The block takes three arguments:
 obj
 The element in the ordered set.
 idx
 The index of the element in the ordered set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the ordered set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 By default, the enumeration starts with the first object and continues serially through the ordered set to the last element specified by indexSet. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Returns the indexes of objects in the ordered set that conform to the given protocol.
 
 @param protocol
 The Protocol which objects in the ordered set must conform to for their index to be returned in the index set
 
 @return
 The indexes whose corresponding values in the ordered set are the kind of object class passed. If no objects in the ordered set pass the test, returns an empty index set.
 */
- (NSIndexSet *)indexesOfObjectsConformingToProtocol:(Protocol *)protocol;

@end

@interface NSSet (SafeCast)

#pragma mark - Responds to Selector

/**
 Sends to each object in the set the message identified by a given selector, starting with the first object and continuing through the set to the last object if and only if the object responds to the given selector.
 
 This method raises an NSInvalidArgumentException if aSelector is NULL.
 
 @param aSelector A selector that identifies the message to send to the objects in the set. The method must not take any arguments, and must not have the side effect of modifying the receiving set.
 
 Availability
 Available in iOS 2.0 and later.
 
 @see - makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)makeObjectsSafelyPerformSelector:(SEL)aSelector;

/**
 Sends the aSelector message to each object in the set, starting with the first object and continuing through the set to the last object if and only if the object responds to the given selector.
 
 This method raises an NSInvalidArgumentException if aSelector is NULL.
 
 @param aSelector A selector that identifies the message to send to the objects in the set. The method must take a single argument of type id, and must not have the side effect of modifying the receiving set.
 
 @param anObject The object to send as the argument to each invocation of the aSelector method.
 
 @see - makeObjectsPerformSelectorSafely:
 @see – makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)makeObjectsSafelyPerformSelector:(SEL)aSelector withObject:(id)anObject;

/**
 Executes a given block using each object in the set matching the indicated Class, starting with the first object and continuing through the set to the last object.
 
 If the Block parameter is nil this method will raise an exception.
 
 This method executes synchronously.
 
 @param class
 The Class objects in the set must be a kind of for the block to be executed on
 @param block
 The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 @see – enumerateObjectsWithOptions:usingBlock:
 @see – makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsOfKind:(Class)class usingBlock:(void (^)(id obj, BOOL *stop))block;

/**
 Executes a given block using each object in the set.
 
 @param class
 The Class objects in the set must be a kind of for the block to be executed on
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @param block
 The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 By default, the enumeration starts with the first object and continues serially through the set to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsOfKind:(Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, BOOL *stop))block;

#pragma mark - Protocols NSSet

/**
 Executes a given block using each object in the set matching the indicated Class, starting with the first object and continuing through the set to the last object.
 
 If the Block parameter is nil this method will raise an exception.
 
 This method executes synchronously.
 
 @param protocol
 The Protocol objects in the set must be a kind of for the block to be executed on
 @param block
 The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 @see – enumerateObjectsWithOptions:usingBlock:
 @see – makeObjectsPerformSelector:
 @see – makeObjectsPerformSelector:withObject:
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol usingBlock:(void (^)(id obj, BOOL *stop))block;

/**
 Executes a given block using each object in the set.
 
 @param protocol
 The Protocol objects in the set must be a kind of for the block to be executed on
 @param opts
 A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
 @param block
 The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 
 By default, the enumeration starts with the first object and continues serially through the set to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.
 
 This method executes synchronously.
 
 @methodgroup Sending Messages to Elements
 */
- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, BOOL *stop))block;

@end

@interface NSDictionary (SafeCast)

/**
 Applies a given block object to the entries of the dictionary if the object is of the specified kind.
 
 
 @param class
 The Class objects in the receiver must be a kind of in order to have the block operate on them
 @param block
 A block object to operate on entries in the dictionary.
 
 @see – enumerateKeysAndObjectsWithOptions:usingBlock:
*/
- (void)enumerateKeysAndObjectsOfKind:(Class)class usingBlock:(void (^)(id key, id obj, BOOL *stop))block;

/**
Applies a given block object to the entries of the dictionary if the object conforms to the specified Protocol.

 @param protocol
 The Protocol objects in the receiver must conform to in order to have the block operate on them
 @param block
 A block object to operate on entries in the dictionary.

@see – enumerateKeysAndObjectsWithOptions:usingBlock:
*/
- (void)enumerateKeysAndObjectsConformingToProtocol:(Protocol *)protocol usingBlock:(void (^)(id key, id obj, BOOL *stop))block;

/**
 Applies a given block object to the entries of the dictionary if the are of the specified kind.
 
 @param class
 The Class objects in the receiver must be a kind of in order to have the block operate on them
 @param opts
 Enumeration options.
 @param block
 A block object to operate on entries in the dictionary.

 If the block sets *stop to YES, the enumeration stops.
 
 @see – enumerateKeysAndObjects:usingBlock:
 */
- (void)enumerateKeysAndObjectsOfKind:(Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id key, id obj, BOOL *stop))block;

/**
 Applies a given block object to the entries of the dictionary if the conform to the specified Protocol.

 @param protocol
 The Protocol objects in the receiver must conform to in order to have the block operate on them
 @param opts
 Enumeration options.
 @param block
 A block object to operate on entries in the dictionary.

 If the block sets *stop to YES, the enumeration stops.
 
 @see – enumerateKeysAndObjects:usingBlock:
 */
- (void)enumerateKeysAndObjectsConformingToProtocol:(Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id key, id obj, BOOL *stop))block;


@end
