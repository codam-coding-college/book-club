from typing import List
from logger import Logger
from subject import Subject


class LogAggregator(Subject):

    def __init__(self) -> None:
        super().__init__()
        self._observers: List[Logger] = []

    def register(self, o: Logger) -> None:
        self._observers.append(o)

    def remove(self, o: Logger) -> None:
        self._observers.remove(o)

    def notify(self, msg: str) -> None:
        for logger in self._observers:
            logger.update(msg)
