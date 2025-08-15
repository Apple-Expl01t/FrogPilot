import time
import functools

from openpilot.common.swaglog import cloudlog


def retry(attempts=3, delay=1.0, ignore_failure=False):
  def decorator(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
      for _ in range(attempts):
        try:
          return func(*args, **kwargs)
        except (KeyboardInterrupt, SystemExit, MemoryError):
          # Don't retry critical system exceptions
          raise
        except Exception as e:
          cloudlog.exception(f"{func.__name__} failed, trying again: {e}")
          time.sleep(delay)

      if ignore_failure:
        cloudlog.error(f"{func.__name__} failed after retry")
        return None
      else:
        raise Exception(f"{func.__name__} failed after {attempts} retry attempts")
    return wrapper
  return decorator


if __name__ == "__main__":
  @retry(attempts=10)
  def abc():
    raise ValueError("abc failed :(")
  abc()
