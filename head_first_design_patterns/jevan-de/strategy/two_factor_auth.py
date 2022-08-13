from sys import stdout
from login import Login


class TwoFactorAuth(Login):

    def __init__(self) -> None:
        super().__init__()

    def login(self) -> None:
        print("Loggin in with two factor authentication", file=stdout)
