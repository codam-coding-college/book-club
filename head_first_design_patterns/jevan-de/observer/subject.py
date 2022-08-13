from observer import Observer
from abc import ABC, abstractmethod


class Subject(ABC):

    def __init__(self) -> None:
        super().__init__()

    @abstractmethod
    def register(self, o: Observer) -> None: raise NotImplementedError

    @abstractmethod
    def remove(self, o: Observer) -> None: raise NotImplementedError

    @abstractmethod
    def notify(self) -> None: raise NotImplementedError
