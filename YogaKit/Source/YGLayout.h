/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#define UIView NSView
#define UIControl NSControl
#define UIEdgeInsets NSEdgeInsets
#define UIEdgeInsetsMake NSEdgeInsetsMake
#else
#import <UIKit/UIKit.h>
#endif

@import Yoga;

@class YGLayout;

NS_ASSUME_NONNULL_BEGIN

typedef void (^YGLayoutConfigurationBlock)(YGLayout* layout);

NS_INLINE YGValue YGPointValue(CGFloat value) NS_SWIFT_UNAVAILABLE("Use the swift Int and FloatingPoint extensions instead") {
    return (YGValue){ value, YGUnitPoint };
}

NS_INLINE YGValue YGPercentValue(CGFloat value) NS_SWIFT_UNAVAILABLE("Use the swift Int and FloatingPoint extensions instead") {
    return (YGValue){ value, YGUnitPercent };
}

typedef NS_OPTIONS(NSInteger, YGDimensionFlexibility) {
    YGDimensionFlexibilityFlexibleWidth = 1 << 0,
    YGDimensionFlexibilityFlexibleHeight = 1 << 1,
};

@interface YGLayout : NSObject

/**
 Make default init unavailable, as it will not initialise YGNode which is
 required for the setters and getters of YGLayout's properties to work properly.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Make default init unavailable, as it will not initialise YGNode which is
 required for the setters and getters of YGLayout's properties to work properly.
 */
+ (instancetype)new NS_UNAVAILABLE;

/**
  The property that decides if we should include this view when calculating
  layout. Defaults to YES.
 */
@property(nonatomic, setter=setIncludedInLayout:) BOOL isIncludedInLayout;

/**
 Get the resolved direction of this node. This won't be YGDirectionInherit
 */
@property(nonatomic, readonly) YGDirection resolvedDirection;

/**
 Perform a layout calculation and update the frames of the views in the
 hierarchy with the results. If the origin is not preserved, the root view's
 layout results will applied from {0,0}.
 */
- (void)applyLayoutPreservingOrigin:(BOOL)preserveOrigin
    NS_SWIFT_NAME(applyLayout(preservingOrigin:));

/**
 Perform a layout calculation and update the frames of the views in the
 hierarchy with the results. If the origin is not preserved, the root view's
 layout results will applied from {0,0}.
 */
- (void)applyLayoutPreservingOrigin:(BOOL)preserveOrigin
               dimensionFlexibility:(YGDimensionFlexibility)dimensionFlexibility
    NS_SWIFT_NAME(applyLayout(preservingOrigin:dimensionFlexibility:));

/**
 Returns the size of the view if no constraints were given. This could
 equivalent to calling [self sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
 */
@property(nonatomic, readonly) CGSize intrinsicSize;

/**
  Returns the size of the view based on provided constraints. Pass NaN for an
  unconstrained dimension.
 */
- (CGSize)calculateLayoutWithSize:(CGSize)size
    NS_SWIFT_NAME(calculateLayout(size:));

/**
 Returns the number of children that are using Flexbox.
 */
@property(nonatomic, readonly) NSUInteger numberOfChildren;

/**
 Return a BOOL indiciating whether or not we this node contains any subviews
 that are included in Yoga's layout.
 */
@property(nonatomic, readonly) BOOL isLeaf;

/**
 Return's a BOOL indicating if a view is dirty. When a node is dirty
 it usually indicates that it will be remeasured on the next layout pass.
 */
@property(nonatomic, readonly) BOOL isDirty;

/**
 Mark that a view's layout needs to be recalculated. Only works for leaf views.
 */
- (void)markDirty;

/**
 In ObjC land, every time you access `view.yoga.*` you are adding another
 `objc_msgSend` to your code. If you plan on making multiple changes to
 YGLayout, it's more performant to use this method, which uses a single
 objc_msgSend call.
 */
- (void)configureLayoutWithBlock:(NS_NOESCAPE YGLayoutConfigurationBlock)block
    NS_SWIFT_NAME(configureLayout(block:));

@end

@interface YGLayout (Properties)

@property(nonatomic) YGDirection direction;
@property(nonatomic) YGFlexDirection flexDirection;
@property(nonatomic) YGJustify justifyContent;
@property(nonatomic) YGAlign alignContent;
@property(nonatomic) YGAlign alignItems;
@property(nonatomic) YGAlign alignSelf;
@property(nonatomic) YGPositionType position;
@property(nonatomic) YGWrap flexWrap;
@property(nonatomic) YGOverflow overflow;
@property(nonatomic) YGDisplay display;

@property(nonatomic) CGFloat flex;
@property(nonatomic) CGFloat flexGrow;
@property(nonatomic) CGFloat flexShrink;
@property(nonatomic) YGValue flexBasis;

@property(nonatomic) YGValue left;
@property(nonatomic) YGValue top;
@property(nonatomic) YGValue right;
@property(nonatomic) YGValue bottom;
@property(nonatomic) YGValue start;
@property(nonatomic) YGValue end;

@property(nonatomic) YGValue marginLeft;
@property(nonatomic) YGValue marginTop;
@property(nonatomic) YGValue marginRight;
@property(nonatomic) YGValue marginBottom;
@property(nonatomic) YGValue marginStart;
@property(nonatomic) YGValue marginEnd;
@property(nonatomic) YGValue marginHorizontal;
@property(nonatomic) YGValue marginVertical;
@property(nonatomic) YGValue margin;

@property(nonatomic) YGValue paddingLeft;
@property(nonatomic) YGValue paddingTop;
@property(nonatomic) YGValue paddingRight;
@property(nonatomic) YGValue paddingBottom;
@property(nonatomic) YGValue paddingStart;
@property(nonatomic) YGValue paddingEnd;
@property(nonatomic) YGValue paddingHorizontal;
@property(nonatomic) YGValue paddingVertical;
@property(nonatomic) YGValue padding;

@property(nonatomic) CGFloat borderLeftWidth;
@property(nonatomic) CGFloat borderTopWidth;
@property(nonatomic) CGFloat borderRightWidth;
@property(nonatomic) CGFloat borderBottomWidth;
@property(nonatomic) CGFloat borderStartWidth;
@property(nonatomic) CGFloat borderEndWidth;
@property(nonatomic) CGFloat borderWidth;

@property(nonatomic) YGValue width;
@property(nonatomic) YGValue height;
@property(nonatomic) YGValue minWidth;
@property(nonatomic) YGValue minHeight;
@property(nonatomic) YGValue maxWidth;
@property(nonatomic) YGValue maxHeight;

// Yoga specific properties, not compatible with flexbox specification
@property(nonatomic) CGFloat aspectRatio;

- (void)setGap:(YGValue)gap forGutter:(YGGutter)gutter;
- (YGValue)gapForGutter:(YGGutter)gutter;

@end

#pragma mark -

@interface YGLayout (Point)

// top, left, bottom, right of margin
@property(nonatomic) UIEdgeInsets margins;

// top, left, bottom, right of padding
@property(nonatomic) UIEdgeInsets paddings;

// width, height
@property(nonatomic) CGSize size;

// top, left, bottom, right
@property(nonatomic) UIEdgeInsets edges;

@end

@interface YGLayout (Display)

// set value for isIncludedInLayout and hidden of View
@property(nonatomic) BOOL isHidden;

@end

NS_ASSUME_NONNULL_END
