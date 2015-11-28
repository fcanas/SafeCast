task :default => [:lint_podspec, :run_tests]

task :lint_podspec do
  sh("#{LINT_TOOL} #{LINT_FLAGS}")
end

task :run_tests_ios => [:clean, :pod_install] do
  sh("#{BUILD_TOOL} #{BUILD_FLAGS_TEST_IOS} | #{PRETTIFY}")
end

task :pod_install do
  sh("cd xcode; pod install")
end

task :clean do
  sh("rm -rf '#{DERIVED_DATA_PATH}'")
end

task :run_tests => [:run_tests_ios]

private

LIBRARY_NAME = 'SafeCast'

WORKSPACE_PATH = "xcode/#{LIBRARY_NAME}.xcworkspace"
PODSPEC_PATH = "#{LIBRARY_NAME}.podspec"
DERIVED_DATA_PATH = "#{ENV['HOME']}/Library/Developer/Xcode/DerivedData"
DESTINATION = 'platform=iOS Simulator,name=iPhone 5,OS=latest'

LINT_TOOL = 'bundle exec pod lib lint'
BUILD_TOOL = 'xcodebuild'

LINT_FLAGS = "#{PODSPEC_PATH}"
BUILD_FLAGS =
  "-workspace '#{WORKSPACE_PATH}' "\
  "-derivedDataPath '#{DERIVED_DATA_PATH}'"
BUILD_FLAGS_IOS = BUILD_FLAGS + " -destination '#{DESTINATION}'"
BUILD_FLAGS_TEST_IOS = "test -scheme '#{LIBRARY_NAME}_' " + BUILD_FLAGS_IOS

PRETTIFY = "xcpretty --color; exit ${PIPESTATUS[0]}"