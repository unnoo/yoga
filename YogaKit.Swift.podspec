# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

podspec = Pod::Spec.new do |spec|
  spec.name = 'YogaKit.Swift'
  spec.version = '1.18.2'
  spec.license =  { :type => 'MIT', :file => "LICENSE" }
  spec.homepage = 'https://facebook.github.io/yoga/'
  spec.documentation_url = 'https://facebook.github.io/yoga/docs/'

  spec.summary = 'Yoga is a cross-platform layout engine which implements Flexbox.'
  spec.description = 'Yoga is a cross-platform layout engine enabling maximum collaboration within your team by implementing an API many designers are familiar with, and opening it up to developers across different platforms.'

  spec.authors = 'Facebook'
  spec.source = {
    :git => 'https://github.com/facebook/yoga.git',
    :tag => "1.18.0",
  }

  spec.platforms = { :ios => "9.0", :osx => "10.9", :tvos => "9.0" }
  spec.module_name = 'YogaKitSwift'
  spec.dependency 'Yoga', '~> 1.14.1'
  spec.dependency 'YogaKit', '~> 1.18.2'
  # Fixes the bug related the xcode 11 not able to find swift related frameworks.
  # https://github.com/Carthage/Carthage/issues/2825
  # https://twitter.com/krzyzanowskim/status/1151549874653081601?s=21
  spec.pod_target_xcconfig = {"LD_VERIFY_BITCODE": "NO"}
  spec.source_files = 'YogaKit/YogaKit.Swift/*.swift'
  spec.swift_version = '5.0'
  spec.static_framework = true
end

# See https://github.com/facebook/yoga/pull/366
podspec.attributes_hash["readme"] = "YogaKit/README.md"
podspec
