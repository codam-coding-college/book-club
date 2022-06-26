from curses.ascii import US
from user import User
from oauth import OAuth
from two_factor_auth import TwoFactorAuth


def main() -> None:
    oauth_login = OAuth()

    user = User(oauth_login)
    user.login()

    two_factor_login = TwoFactorAuth()

    user.login_behaviour = two_factor_login
    user.login()


if __name__ == '__main__':
    main()
