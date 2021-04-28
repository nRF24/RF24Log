# Supported Format Specifiers

## Conditional dependency
Native printf supported platforms will default to said support.

### Arduino Platform Supported Specifiers
Because all Arduino cores for all Arduino compatible boards don't unanimously support
printf, we have a basic imitation mechanism included with ArduinoPrintLogger.

The format specifiers' usage:
```text
%[flags][pad_quantity].[precision_quantity]specifier
```
@note The only supported flags are zero (`0`) for padding data with zeros instead of spaces.

The following list of characters that follow a % symbol (or a `pad_quantity` number)
will signify that the corresponding argument is of a certain datatype.

| Specifier | relative datatype |
|----------:|:------------------|
| `F` / `D` | a double |
| `s` / `S` | a string |
| `d` / `i` / `l` / `u` | an integer |
| `x` / `X` | a hexadecimal integer |
| `o` | an octal integer |
| `b` | a binary integer |
| `c` | a single character |

@warning Only the Arduino AVR platform supports a string (from flash memory)
specifier's capitol (`S`) syntax because of the special `__FlashStringHelper`
implementation. All other platforms should support using `s` for strings.

@note You can escape % symbols by pairing to of them together (like %%).

#### Padding the numbers
For each numeric data specifier, a quantity of padded zeros (`0`) can be
specified before the specifer (but immediately after the % symbol).

For example:
```cpp
RF24Log_info("exampleVendor", "0x%02x %%", 0xf);
// prints:     60176; INFO  ;exampleVendor;0x0F %

RF24Log_info("exampleVendor", "%02x", 0xa0);
// prints:     60176; INFO  ;exampleVendor;A0

RF24Log_info("exampleVendor", "%.2F", 3.1459);
// prints:     60176; INFO  ;exampleVendor;3.14
```

@note Floats/Doubles will only use the precision quantity as the resolution of decimal places.
Specifying quantity of insignificant zeroes on the whole numbers of floats/doubles is not supported.

@note Octal and hexadecimal integers are padded with zeros. Characters and
decimal integers are padded with spaces.
