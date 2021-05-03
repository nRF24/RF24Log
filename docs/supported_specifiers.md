# Supported Format Specifiers

## Arduino Platform Supported Specifiers
Because all Arduino cores for all Arduino compatible boards don't unanimously support
printf, we have a basic imitation mechanism included with RF24LogPrintfParser.

The format specifiers' usage:
```text
%[flags][pad_quantity][.precision_quantity]specifier
```

The following list of characters that follow a % symbol (or a
`flag`/`pad_quantity`/`precision_quantity` option) will signify that the corresponding
argument is of a certain datatype.

| Specifier | Representation |
|----------:|:------------------|
| `F` / `D` | a double |
| `s` / `S` | a string |
| `d` / `i` / `l` | a signed integer |
| `du` / `iu` / `u` / `lu` | an unsigned integer |
| `x` / `X` | an unsigned hexadecimal integer |
| `o` | an unsigned octal integer |
| `b` | an unsigned binary integer |
| `c` | a single character |
| % | escapes a single % character |

### Limitations
These are the differences to standard printf parsing and our in-house printf parsing:

- Floats/doubles will only use the `precision_quantity` as the number of decimal places.
  Specifying a `pad_quantity` for padding the whole numbers of floats/doubles is not
  supported (thus the `pad_quantity` has no affect on floats and doubles).
- Only the Arduino AVR platform supports a string (from flash memory)
  specifier's capitol (`S`) syntax because of the special `__FlashStringHelper`
  implementation. All other platforms support using `s` for strings.
- The only supported flags are zero (`0`) for padding data with zeros instead of spaces.
  Other flags (`+`, `-`, ` `) have no affect.
- The `u` character will enforce numeric data to be interpreted as an `unsigned long` number.
Otherwise, all numeric data is represented as a signed `long` number (`float` and `double`
variables are represented as a `double`).

### Padding the numbers
For each numeric data specifier, a quantity of padded characters can be
designated before the specifer (but immediately after the % symbol). The default
character used for padding is a space (` `), but putting a zero (`0`) character
`flag` before the `padding_quantity` changes the padding character to zeros (`0`).

For example:
```cpp
const char vID[] = "specifier fmt";
RF24Log_info(vID, "0x%02x %%", 0xf); // prints:     60176; INFO  ;specifier fmt;0x0F %
RF24Log_info(vID, "%4x", 0xa0);      // prints:     60178; INFO  ;specifier fmt;  A0
RF24Log_info(vID, "%.2F", 3.1459);   // prints:     60180; INFO  ;specifier fmt;3.14
RF24Log_info(vID, "%.4F", 2.71);     // prints:     60182; INFO  ;specifier fmt;2.7100
```
