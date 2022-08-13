import logging
from sys import stdout
from typing import TextIO
from uuid import uuid4
from observer import Observer


class Logger(Observer):

    def __init__(self, file: TextIO = stdout) -> None:
        super().__init__()
        self._logger    = logging.getLogger(str(uuid4()))
        handler         = logging.StreamHandler(file)
        formatter       = logging.Formatter('%(asctime)s %(levelname)s %(name)s - %(message)s')
        handler.setFormatter(formatter)

        self._logger.setLevel(logging.INFO)
        self._logger.addHandler(handler)

    def update(self, msg: str) -> None:
        self.log(msg)

    def log(self, msg: str) -> None:
        self._logger.info(msg)
