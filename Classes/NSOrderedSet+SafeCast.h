//
//  NSOrderedSet+SafeCast.h
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

/**
 Type-safe operations on elements of an NSOrderedSet.
 
 This category enables some type and behavior dependent operations on elements of an NSOrderedSet.
 It is possible to perform actions such as enumeration, finding indices, and performing selectors on member objects based on criteria such as they kind, their adoption of a protocol, or whether they respond to a selector.
 */
@interface NSOrderedSet (SafeCast)

#pragma mark - Kind of Class

/**
 @name Operations on objects that are a kind of class.
 */

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
 
 @methodgroup Sending Messages to Elements
 */
- (void)safe_enumerateObjectsOfKind:(Class)class usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

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
- (void)safe_enumerateObjectsOfKind:(Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

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
- (void)safe_enumerateObjectsOfKind:(Class)class AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Returns the indexes of objects in the ordered set that are of the kind of the given Class.
 
 @param class
 The Class objects in the ordered set must be a kind of for their index to be returned in the index set
 
 @return
 The indexes whose corresponding values in the ordered set are the kind of object class passed. If no objects in the ordered set pass the test, returns an empty index set.
 */
- (NSIndexSet *)safe_indexesOfObjectsOfKind:(Class)class;

#pragma mark - Conforms to Protocol

/**
 @name Operations on objects that conform to a protocol
 */

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
 
 @methodgroup Sending Messages to Elements
 */
- (void)safe_enumerateObjectsConformingToProtocol:(Protocol *)protocol usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

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
- (void)safe_enumerateObjectsConformingToProtocol:(Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

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
- (void)safe_enumerateObjectsConformingToProtocol:(Protocol *)protocol AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Returns the indexes of objects in the ordered set that conform to the given protocol.
 
 @param protocol
 The Protocol which objects in the ordered set must conform to for their index to be returned in the index set
 
 @return
 The indexes whose corresponding values in the ordered set are the kind of object class passed. If no objects in the ordered set pass the test, returns an empty index set.
 */
- (NSIndexSet *)safe_indexesOfObjectsConformingToProtocol:(Protocol *)protocol;

#pragma mark - Responds to Selector

/**
 @name Operations on objects that respond to a selector.
 */

/**
 Executes a given block using each object in the ordered set which can respond to the given selector, starting with the first object and continuing through the ordered set to the last object.

 If the Block parameter is nil this method will raise an exception.

 This method executes synchronously.

 @param selector The selector objects in the ordered set must respond to for the block to be executed on
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
 
 @methodgroup Sending Messages to Elements
 */
- (void)safe_enumerateObjectsRespondingToSelector:(SEL)selector usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using each object in the ordered set which can respond to the given selector.
 
 @param selector The selector objects in the ordered set must respond to for the block to be executed on
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
- (void)safe_enumerateObjectsRespondingToSelector:(SEL)selector withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 Executes a given block using the objects in the ordered set at the specified indexes which can respond to the given selector.
 
 @param selector The selector objects in the ordered set must respond to for the block to be executed on
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
- (void)safe_enumerateObjectsRespondingToSelector:(SEL)selector atIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

@end
