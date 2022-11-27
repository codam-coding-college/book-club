import pytest
from count_end_with import count_end_with

# Run tests with coverage:  `coverage run -m pytest -rP --verbosity=1`
# Generate console report:  `coverage report`
# Generate web report:      `coverage html`

# NOTES
# Line converage:
# Condition coverage:
# Branch coverage:
# Path coverage:

@pytest.mark.parametrize(
    argnames='s,a,b',
    argvalues=[
        ('', '', ''),
        ('a', 'a', 'b'),
        ('abc', 'a', 'b'),
        ('abc abc', 'a', 'b')
    ]
)
def test_zero_return(s: str, a: str, b: str):
    assert count_end_with(s, a, b) == 0

@pytest.mark.parametrize(
    argnames='s,a,b',
    argvalues=[
        ('abc abc', 'ab', 'b'),
        ('abc abc', 'a', 'ab'),
        ('abc abc', '1', 'b'),
        ('abc abc', 'a', '1')
    ] 
)
def test_invalid_input(s: str, a: str, b: str):
    with pytest.raises(ValueError):
        count_end_with(s, a, b)

@pytest.mark.parametrize(
    argnames='s,a,b,count',
    argvalues=[
        ('abc', 'a', 'c', 1),
        ('abc', 'c', 'a', 1),
        ('abc abc', 'a', 'c', 2),
        ('abc ab abc', 'a', 'c', 2),
    ]  
)
def test_valid_input(s: str, a: str, b: str, count: int):
    assert count_end_with(s, a, b) == count
