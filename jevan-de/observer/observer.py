from abc import ABC, abstractmethod


class Observer(ABC):

    def __init__(self) -> None:
        super().__init__()

    @abstractmethod
    def update(self, msg: str) -> None: raise NotImplementedError
