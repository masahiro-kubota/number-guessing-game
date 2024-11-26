# Additional Feature
## Concurrency Output of current counts and elapsed time
- The system serve current counts and elapsed time every 1 second
- If `asyncio` isn't used, the system can't serve them during inputting and players can't input answers during hints are providing.

## Time limit
- Players need to find the secret number within 10 seconds
- If `asycio` and `aioconsole` isn't used, the program cannot terminate even if the time is over.

### supplement
- input() is blocking, so this program uses aioconsole.ainput() to use non-blocking input method.
  - In python, to kill blocking is difficult. 

```
uv sync
. .venv/bin/activate
./main.py
```
