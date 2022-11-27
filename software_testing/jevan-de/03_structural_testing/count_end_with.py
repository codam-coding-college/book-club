from functools import reduce

def count_end_with(s: str, a: str, b: str) -> int:
    """
    Given a string `s`, this function counts the number of words ending in char `a` or `b`
    
    So with a='y' and b='z' the 'y' in "heavy" and the 'z' in "fez" count, but not
    the 'y' in "yellow" (not case sensitive). We'll say that a y or z is at the end
    of a word if there is not an alphabetic letter immediately following it.

    Words are delimited by spaces.
    """

    if len(s) < 2:
        return 0
    
    if len(a) != 1 or len(b) != 1 or not a.isalpha() or not b.isalpha():
        raise ValueError(
            f'Invalid arguments. Make sure `a` and `b` are alphanumeric characters.'
        )
    
    words = s.split()
    def word_endswith(incr: int, c: str) -> bool:
        return incr + 1 if c.endswith(a) or c.endswith(b) else incr

    return reduce(word_endswith, words, 0)
    