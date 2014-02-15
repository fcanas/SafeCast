#
#  Be sure to run `pod spec lint SafeCast.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|
  s.name         = "SafeCast"
  s.version      = "0.0.1"
  s.summary      = "Safe Casting in Objective-C"

  s.description  = <<-DESC
                  * Cast in Objective-C, not in C
                  * Be Safe
                  * Be Concice

                   Objective-C is C, and C can be perilous. Don't blindly cast objects. Stick to high-level language features, and write more readable code.

                   Quite simply, you can do things like this:

                  ```
                   NSMutableArray *mArray = [NSMutableArray cast:array];
                   // `mArray` is nil if `array` is not a mutable array, and is `array` if it is.
                   ```
                  DESC

  s.homepage     = "https://github.com/fcanas/SafeCast"
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author             = { "Fabian Canas" => "fcanas@gmail.com" }
  # s.social_media_url = "http://twitter.com/Fabian Canas"
  # ――― Platform Specifics ――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  If this Pod runs only on iOS or OS X, then specify the platform and
  #  the deployment target. You can optionally include the target after the platform.
  #

  # s.platform     = :ios
  # s.platform     = :ios, '5.0'

  #  When using multiple platforms
  # s.ios.deployment_target = '5.0'
  # s.osx.deployment_target = '10.7'
  s.source       = { :git => "https://github.com/fcanas/SafeCast.git", :tag => "v0-alpha.1" }

  s.source_files  = 'Classes', 'Classes/**/*.{h,m}'
  # s.exclude_files = 'Classes/Exclude'
  # s.public_header_files = 'Classes/**/*.h'


  # ――― Resources ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  A list of resources included with the Pod. These are copied into the
  #  target bundle with a build phase script. Anything else will be cleaned.
  #  You can preserve files from being cleaned, please don't preserve
  #  non-essential files like tests, examples and documentation.
  #

  # s.resource  = "icon.png"
  # s.resources = "Resources/*.png"

  # s.preserve_paths = "FilesToSave", "MoreFilesToSave"


  # ――― Project Linking ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  Link your library with frameworks, or libraries. Libraries do not include
  #  the lib prefix of their name.
  #

  # s.framework  = 'SomeFramework'
  # s.frameworks = 'SomeFramework', 'AnotherFramework'

  # s.library   = 'iconv'
  # s.libraries = 'iconv', 'xml2'


  # ――― Project Settings ――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  If your library depends on compiler flags you can set them in the xcconfig hash
  #  where they will only apply to your library. If you depend on other Podspecs
  #  you can include multiple dependencies to ensure it works.

  # s.requires_arc = true

  # s.xcconfig = { 'HEADER_SEARCH_PATHS' => '$(SDKROOT)/usr/include/libxml2' }
  # s.dependency 'JSONKit', '~> 1.4'

end
