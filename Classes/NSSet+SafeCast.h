//
//  NSSet+SafeCast.h
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
 Type-safe operations on elements of an NSSet.
 
 This category enables some type and behavior dependent operations on elements of an NSSet.
 It is possible to perform actions such as enumeration and performing selectors on member objects based on criteria such as they kind, their adoption of a protocol, or whether they respond to a selector.
 */
@interface NSSet (SafeCast)

#pragma mark - Perform selector

/**
 @name Performing a selector
 */

/**
 Sends to each object in the set the message identified by a given selector, if and only if the object responds to the given selector.
 
 This method raises an NSInvalidArgumentException if aSelector is NULL.
 
 @param aSelector A selector that identifies the message to send to the objects in the set. The method must not take any arguments, and must not have the side effect of modifying the receiving set.
 
 @see - safe_makeObjectsSafelyPerformSelector:withObject:
 */
- (void)safe_makeObjectsSafelyPerformSelector:(nonnull SEL)aSelector;

/**
 Sends a selector message to each object in the set, if and only if the object responds to the given selector.

 This method raises an NSInvalidArgumentException if aSelector is NULL.

 @param aSelector A selector that identifies the message to send to the objects in the set. The method must take a single argument of type id, and must not have the side effect of modifying the receiving set.

 @param anObject The object to send as the argument to each invocation of the aSelector method.

 @see - safe_makeObjectsSafelyPerformSelector:
 */
- (void)safe_makeObjectsSafelyPerformSelector:(nonnull SEL)aSelector withObject:(nonnull id)anObject;

#pragma mark - Of Kind

/**
 @name Operations on objects that are of a kind of class.
 */

/**
 Executes a given block using each object in the set matching the indicated Class, starting with the first object and continuing through the set to the last object.

 If the Block parameter is nil this method will raise an exception.

 This method executes synchronously.

 @param class The Class objects in the set must be a kind of for the block to be executed on

 @param block The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)safe_enumerateObjectsOfKind:(nonnull Class)class usingBlock:(nonnull void (^)(__nonnull id obj, BOOL * __nonnull stop))block;

/**
 Executes a given block using each object in the set.

 @param class The Class objects in the set must be a kind of for the block to be executed on

 @param opts A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).

 @param block The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.

 By default, the enumeration starts with the first object and continues serially through the set to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.

 This method executes synchronously.
 */
- (void)safe_enumerateObjectsOfKind:(nonnull Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(nonnull void (^)(__nonnull id obj, BOOL * __nonnull stop))block;

#pragma mark - Protocols

/**
 @name Operations on objects that conform to a protocol.
 */

/**
 Executes a given block using each object in the set matching the indicated Class, starting with the first object and continuing through the set to the last object.

 If the Block parameter is nil this method will raise an exception.

 This method executes synchronously.

 @param protocol The Protocol objects in the set must be a kind of for the block to be executed on

 @param block The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)safe_enumerateObjectsConformingToProtocol:(nonnull Protocol *)protocol usingBlock:(nonnull void (^)(__nonnull id obj, BOOL * __nonnull stop))block;

/**
 Executes a given block using each object in the set.

 @param protocol The Protocol objects in the set must be a kind of for the block to be executed on

 @param opts A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).

 @param block The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.

 By default, the enumeration starts with the first object and continues serially through the set to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.

 This method executes synchronously.
 */
- (void)safe_enumerateObjectsConformingToProtocol:(nonnull Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(nonnull void (^)(__nonnull id obj, BOOL * __nonnull stop))block;

/**
 @name Operations on objects that respond to a selector.
 */

/**
 Executes a given block using each object in the set which can respond to the given selector, starting with the first object and continuing through the set to the last object.
 
 If the Block parameter is nil this method will raise an exception.
 
 This method executes synchronously.
 
 @param selector The selector objects in the ordered set must respond to for the block to be executed on them

 @param block The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)safe_enumerateObjectsRespondingToSelector:(nonnull SEL)selector usingBlock:(nonnull void (^)(__nonnull id obj, BOOL * __nonnull stop))block;

/**
 Executes a given block using each object in the set which can respond to the given selector.
 
 @param selector The selector objects in the ordered set must respond to for the block to be executed on them

 @param opts A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).

 @param block The block to apply to elements in the set.
 The block takes three arguments:
 obj
 The element in the set.
 stop
 A reference to a Boolean value. The block can set the value to YES to stop further processing of the set. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.

 By default, the enumeration starts with the first object and continues serially through the set to the last object. You can specify NSEnumerationConcurrent and/or NSEnumerationReverse as enumeration options to modify this behavior.

 This method executes synchronously.
 */
- (void)safe_enumerateObjectsRespondingToSelector:(nonnull SEL)selector withOptions:(NSEnumerationOptions)opts usingBlock:(nonnull void (^)(__nonnull id obj, BOOL * __nonnull stop))block;

@end