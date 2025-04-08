/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import CoreGraphics
import Yoga

postfix operator %

extension Int {

    @inlinable public static postfix func %(value: Int) -> YGValue {
        return YGValue(value: Double(value), unit: .percent)
    }
}

extension Double {

    @inlinable public static postfix func %(value: Double) -> YGValue {
        return YGValue(value: value, unit: .percent)
    }
}

extension YGValue: @unchecked @retroactive Sendable {}

extension YGValue: @retroactive ExpressibleByIntegerLiteral {

    @inlinable public init(integerLiteral value: Int) {
        self = YGValue(value: Double(value), unit: .point)
    }
}

extension YGValue: @retroactive ExpressibleByFloatLiteral {

    @inlinable public init(floatLiteral value: Double) {
        self = YGValue(value: value, unit: .point)
    }
}

extension YGValue {

    public init(value: Int, unit: YGUnit) {
        self.init(value: Double(value), unit: unit)
    }

    public init(value: CGFloat, unit: YGUnit) {
        self.init(value: Double(value), unit: unit)
    }
}

extension YGValue {
    
    public static let zero = YGValue(value: 0, unit: .point)

    public static let auto = YGValue(value: Double.nan, unit: .auto)

    public static let undefined = YGValue(value: Double.nan, unit: .undefined)
}

extension YGValue {

    @inlinable public static func point(_ value: Int) -> YGValue {
        return YGValue(value: value, unit: .point)
    }

    @inlinable public static func point(_ value: Double) -> YGValue {
        return YGValue(value: value, unit: .point)
    }

    @inlinable public static func point(_ value: CGFloat) -> YGValue {
        return YGValue(value: value, unit: .point)
    }

    @inlinable public static func percent(_ value: Int) -> YGValue {
        return YGValue(value: value, unit: .percent)
    }

    @inlinable public static func percent(_ value: Double) -> YGValue {
        return YGValue(value: value, unit: .percent)
    }

    @inlinable public static func percent(_ value: CGFloat) -> YGValue {
        return YGValue(value: value, unit: .percent)
    }
}
