# Strategy pattern

The idea of the strategy pattern is that you extract a behaviour out of the
class that uses it and modularize it  and then pass it as a dependency. You
could build an interface for the behaviour and then create certain subtypes
based on this. The advantage of this is that you keep things nice and modular
which makes reuse across your codebase a lot more maintainable.

Python does not really provide a way to create interfaces, but does provide
`abc.ABC` for creating abstract classes. This is essentially a wrapper for
the ABCMeta metaclass:
```python
class ABC(metaclass=ABCMeta):
    """Helper class that provides a standard way to create an ABC using
    inheritance.
    """
    __slots__ = ()
```

## Example
A user may have multiple "Login" behaviours. These may also change over time.
Maybe the user switches to using OAuth or 2fa. This is what you will see as an example
in the `main.py` file.
