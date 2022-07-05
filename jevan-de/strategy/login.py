from abc import ABC, abstractmethod

class Login(ABC):

    @abstractmethod
    def login(self) -> None: raise NotImplementedError
