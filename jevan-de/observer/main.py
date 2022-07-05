from logger import Logger
from sys import stderr, stdout
from log_aggregator import LogAggregator


def main() -> None:
    aggr = LogAggregator()
    
    logger_stdout_debug = Logger(file=stdout)
    logger_stderr_error = Logger(file=stderr)

    aggr.register(logger_stdout_debug)
    aggr.register(logger_stderr_error)

    aggr.notify("Observer pattern in action")


if __name__ == '__main__':
    main()
