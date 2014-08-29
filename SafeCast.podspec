Pod::Spec.new do |s|
  s.name         = "SafeCast"
  s.version      = "1.1.0"
  s.summary      = "Safe Casting in Objective-C"
  s.description  = <<-DESC
                  * Cast in Objective-C, not in C
                  * Be Safe
                  * Be Concice
                  
                  Objective-C is C, and C can be perilous. Don't blindly cast objects. Stick to high-level language features, and write more readable code.
                  
                  Quite simply, you can do things like this:
                  
                  ```
                  NSMutableArray *mArray = [NSMutableArray safe_cast:array];
                  // `mArray` is `nil` if `array` is not a mutable array, and is `array` if it is mutable.
                  ```
                  
                  Or only perform a selector if the target responds to it without an explicit check:
                  
                  ```
                  [array safe_makeObjectsSafelyPerformSelector:@selector(method)];
                  ```
                  
                  Or enumerate with a block on objects that are of a specific kind:
                  
                  ```
                  [array safe_enumerateObjectsOfKind:[MyObject class]
                                          usingBlock:^(MyObject *obj, NSUInteger idx, BOOL *stop) {
                                              [obj setNumber:@3];
                                          }];
                  ```
                  
                  And lots of other similar methods on collections.
                  DESC
  s.homepage     = "https://github.com/fcanas/SafeCast"
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author             = { "Fabian Canas" => "fcanas@gmail.com" }
  s.social_media_url = "http://twitter.com/fcanas"
  s.requires_arc = true
  
  s.ios.deployment_target = '4.0'
  s.osx.deployment_target = '10.6'
  
  s.source       = { :git => "https://github.com/fcanas/SafeCast.git", :tag => "v1.1.0" }
  s.source_files  = 'Classes', 'Classes/**/*.{h,m}'
  s.public_header_files = ['Classes/NSArray+SafeCast.h', 'Classes/NSDictionary+SafeCast.h', 'Classes/NSObject+SafeCast.h', 'Classes/NSOrderedSet+SafeCast.h', 'Classes/NSSet+SafeCast.h', 'Classes/SafeCast.h', 'Classes/SafeCastCollections.h']
end
