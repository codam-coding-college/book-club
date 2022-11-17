def substrings_between(_str: str, _open: str, _close: str, /) -> (list[str] | None):
    """
    Searches a string for substrings delimited by a start and end tag, returning all
    matching substrings in an array.
    :param str _str:
        The string containing the substrings. None returns None ; an empty
        string returns another empty string.
    :param str _open:
        The string identifying the start of the substring. An empty string
        returns None.
    :param str _close:
        The string identifying the end of the substring. An empty string
        returns None.
    :return: List of strings containg the matching substrings or None
    :rtype: :class:`~str`
    """
    if _str is None or len(_close) == 0 or len(_open) == 0:
        return None

    def get_next_substring(idx: int) -> (tuple[int, int] | None):
        if (start := _str.find(_open, idx)) == -1:
            return None

        if (end := _str.find(_close, start)) == -1:
            return None

        return start, end

    idx = 0
    matches: list[str] = []
    while (idxs := get_next_substring(idx=idx)) is not None:
        start, end = idxs
        matches.append(_str[start + 1 : end])
        idx = end + 1

    return matches
