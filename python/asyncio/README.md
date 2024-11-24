# Additional Feature
## Concurrency Output of hints
- The system serve hints every 1 second and current number of attempts.
- If `asyncio` isn't used, the system can't serve hints during inputting and players can't input answers during hints are providing.

## Time limit
- Players need to find the secret number within 10 seconds
- If `asycio` isn't used, the program cannot terminate even if the time is over.

### supplement
- input() is blocking, so this program uses aioconsole.ainput() to use non-blocking input method.
  - In python, to kill blocking is difficult. 
