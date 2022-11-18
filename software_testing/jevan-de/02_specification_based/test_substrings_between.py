import pytest
from substrings_between import substrings_between

@pytest.mark.parametrize(
    argnames='_str,_open,_close',
    argvalues=[
        (None, '[', ']'),
        ('[a]', '', ']'),
        ('[a]', '[', '')
    ]
)
def test_wrong_inputs(_str: str, _open: str, _close: str):
    assert substrings_between(_str, _open, _close) is None


@pytest.mark.parametrize(
    argnames='_str,_open,_close',
    argvalues=[
        ('[a[b[c', '[', ']'),
        ('[', '[', ']'),
        (']', '[', ']'),
        ('[][][]', '[', ']'),
    ]
)
def test_empty_list(_str: str, _open: str, _close: str):
    assert substrings_between(_str, _open, _close) == list[str]()


@pytest.mark.parametrize(
    argnames='_str,_open,_close, expected',
    argvalues=[
        ('[a]', '[', ']', ['a']),                               # one substring, 1 character
        ('[a]{b}', '[', ']', ['a']),                
        ('[a][b}', '[', ']', ['a']),
        ('[a]{b]', '[', ']', ['a']),
        ('[a][b][c]', '[', ']', ['a', 'b', 'c']),               # multiple substrings, 1 character
        ('[a]{b][c}', '[', ']', ['a']),
        ('[abc]', '[', ']', ['abc']),                           # one substring, multiple characters
        ('[abc][def][ghi]', '[', ']', ['abc', 'def', 'ghi']),
        ('[abc[[def[ghi]', '[', ']', ['abc[[def[ghi']),
        ('[[[abc]]]', '[', ']', ['[[abc']),                     # nested open en close
    ]
)
def test_substring_matches(_str: str, _open: str, _close: str, expected: list[str]):
    assert substrings_between(_str, _open, _close) == expected
