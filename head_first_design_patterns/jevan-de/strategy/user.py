from login import Login


class User(object):

    def __init__(self, login_behaviour: Login) -> None:
        self.login_behaviour = login_behaviour

    def login(self) -> None:
        self.login_behaviour.login()
