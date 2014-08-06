//
//  NSDictionary.h
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
 Type-safe operations on elements of an NSDictionary.

 This category enables some type and behavior dependent operations on elements of an NSDictionary.
 It is possible to perform actions such as enumeration, and performing selectors on member objects based on criteria such as they kind, their adoption of a protocol, or whether they respond to a selector.
 */
@interface NSDictionary (SafeCast)

#pragma mark - Kind of Class

/**
 @name Operations on objects that are a kind of class.
 */

/**
 Applies a given block object to the entries of the dictionary if the object is of the specified kind.

 @param class
 The Class objects in the receiver must be a kind of in order to have the block operate on them
 @param block
 A block object to operate on entries in the dictionary.

 @see – enumerateKeysAndObjectsWithOptions:usingBlock:
 */
- (void)safe_enumerateKeysAndObjectsOfKind:(Class)class usingBlock:(void (^)(id key, id obj, BOOL *stop))block;

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
- (void)safe_enumerateKeysAndObjectsOfKind:(Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id key, id obj, BOOL *stop))block;

#pragma mark - Conforms to Protocol

/**
 @name Operations on objects that conform to a protocol.
 */

/**
 Applies a given block object to the entries of the dictionary if the object conforms to the specified Protocol.

 @param protocol
 The Protocol objects in the receiver must conform to in order to have the block operate on them
 @param block
 A block object to operate on entries in the dictionary.

 @see – enumerateKeysAndObjectsWithOptions:usingBlock:
 */
- (void)safe_enumerateKeysAndObjectsConformingToProtocol:(Protocol *)protocol usingBlock:(void (^)(id key, id obj, BOOL *stop))block;

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
- (void)safe_enumerateKeysAndObjectsConformingToProtocol:(Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id key, id obj, BOOL *stop))block;

@end