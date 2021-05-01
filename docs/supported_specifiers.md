# Supported Format Specifiers

## Conditional dependency
Native printf supported platforms will default to said support.

### Arduino Platform Supported Specifiers
Because all Arduino cores for all Arduino compatible boards don't unanimously support
printf, we have a basic imitation mechanism included with RF24LogAbstractStream.

The format specifiers' usage:
```text
%[flags][pad_quantity][.precision_quantity]specifier
```
@note The only supported flags are zero (`0`) for padding data with zeros instead of spaces.

The following list of characters that follow a % symbol (or a
`flag`/`pad_quantity`/`precision_quantity` option) will signify that the corresponding
argument is of a certain datatype.

| Specifier | Representation |
|----------:|:------------------|
| `F` / `D` | a double |
| `s` / `S` | a string |
| `d` / `i` / `l` / `u` | an integer |
| `x` / `X` | a hexadecimal integer |
| `o` | an octal integer |
| `b` | a binary integer |
| `c` | a single character |
| % | escapes a single % character |

#### Limitations
- Floats/Doubles will only use the `precision_quantity` as the number of decimal places.
  Specifying a `pad_quantity` for padding the whole numbers of floats/doubles is not
  supported.
- Only the Arduino AVR platform supports a string (from flash memory)
  specifier's capitol (`S`) syntax because of the special `__FlashStringHelper`
  implementation. All other platforms should support using `s` for strings.
- Specifiers that involve more than one alphabetic character are not supported. This
  means %lu will have the same output as %l (and likely the 'u' will still be
  taken/output as literal text).

#### Padding the numbers
For each numeric data specifier, a quantity of padded characters can be
specified before the specifer (but immediately after the % symbol). The default character used for padding is a space (` `), but putting a zero (`0`) character `flag` before the `padding_quantity` changes the padding character to zeros (`0`).

For example:
```cpp
const char vID[] = "specifier fmt";
RF24Log_info(vID, "0x%02x %%", 0xf); // prints:     60176; INFO  ;specifier fmt;0x0F %
RF24Log_info(vID, "%4x", 0xa0);      // prints:     60176; INFO  ;specifier fmt;  A0
RF24Log_info(vID, "%.2F", 3.1459);   // prints:     60176; INFO  ;specifier fmt;3.14
RF24Log_info(vID, "%.4F", 2.71);     // prints:     60176; INFO  ;specifier fmt;2.7100
```
