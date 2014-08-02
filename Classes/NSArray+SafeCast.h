//
//  NSArray+SafeCast.h
//  Pods
//
//  Created by Fabian Canas on 8/2/14.
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

/**
 Type-safe operations on elements of an NSArray.
 
 This category enables some type and behavior dependent operations on elements of an NSArray.
 It is possible to perform actions such as enumeration, finding indices, and performing selectors on member objects based on criteria such as they kind, their adoption of a protocol, or whether they respond to a selector.
 */
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
- (void)safe_makeObjectsSafelyPerformSelector:(SEL)aSelector;

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
- (void)safe_makeObjectsSafelyPerformSelector:(SEL)aSelector withObject:(id)anObject;

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
- (void)safe_enumerateObjectsOfKind:(Class)class usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

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
- (void)safe_enumerateObjectsOfKind:(Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

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
- (void)safe_enumerateObjectsOfKind:(Class)class AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Returns the indexes of objects in the array that are of the kind of the given Class.
 
 @param class
 The Class objects in the array must be a kind of for their index to be returned in the index set
 
 @return
 The indexes whose corresponding values in the array are the kind of object class passed. If no objects in the array pass the test, returns an empty index set.
 */
- (NSIndexSet *)safe_indexesOfObjectsOfKind:(Class)class;

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
- (void)safe_enumerateObjectsConformingToProtocol:(Protocol *)protocol usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

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
- (void)safe_enumerateObjectsConformingToProtocol:(Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

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
- (void)safe_enumerateObjectsConformingToProtocol:(Protocol *)protocol AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Returns the indexes of objects in the array that conform to the given protocol.
 
 @param protocol
 The Protocol which objects in the array must conform to for their index to be returned in the index set
 
 @return
 The indexes whose corresponding values in the array are the kind of object class passed. If no objects in the array pass the test, returns an empty index set.
 */
- (NSIndexSet *)safe_indexesOfObjectsConformingToProtocol:(Protocol *)protocol;

@end
