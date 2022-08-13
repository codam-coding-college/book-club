from sys import stdout
from login import Login


class OAuth(Login):

    def __init__(self) -> None:
        super().__init__()

    def login(self) -> None:
        print("Logging in with open authentication", file=stdout)
