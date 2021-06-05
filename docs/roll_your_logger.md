# How to create your own handler

## What is a handler?
In the scheme of RF24Log naming, a "handler" is simply an object that forwards
log message data to one or more output streams.

## How to customize handler behavior?
By making each output stream inherit from both `RF24LogAbstractHandler` and `RF24LogAbstractStream`,
the output stream will inherit the same `RF24LogAbstractHandler::log()` method that all other
handlers use. Additionally, you can wrap the data being forwarded into more complex or custom
tailored behavior. We call these wrapped contexts handler extentions. The RF24Log library comes with
a sample handler-extention called RF24LogDualHandler located in the "src/handler_ext" folder.
