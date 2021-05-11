# C++ Expressions

## 1. `double x = 42.0f;`
The literal `42.0f` represents of `float` value. This can be converted into `double` without loss of
precision. This conversion is then called *numeric promotion*.

## 2. `float x = 1e-50;`
The literal expression `1e-50` represents a `double` value. It cannot be represented exactly by
single-precision `float` types. Thus, in the initialization happens a conversion and rounding of the
value. The next `float` value is `0.0f`.

## 3. `double x = 1/2;`
The expression `1/2` is integer division. Thus division with a reminder. It results in `0`. Integer
literals like `1` or `2` are always written without any decimal dot.

## 4. `double x = 1.0/2;`
Compared to 3. this expression contains both, a floating-point literal `1.0` and an integer literal `2`.
Thus, we have mixed arithmetic. Whenever floating-point numbers are combined with integer numbers, the
integer is implicitly converted into a floating-point number. Thus we get floating-point division of
`1.0/2.0 = 0.5`.

## 5. `int x = -3ul + 4;`
Here again we have mixed types. `-3ul` is the modulo `N` operation for `unsigned long` types, with
`N` the width of that type. `4` is an `int` value, thus a signed number. Since `unsigned long` is a
"larger" type than `int` is value `4` is converted into `unsigned long`. Then we have a second module
operation and the result is `1`.

**Note:** changing the types slightly, e.g., instead of `unsigned long` we use and `unsigned short`, then
we get a completely different result. Be aware of the type conversion in mixed-type operations. Better:
do not mix types!