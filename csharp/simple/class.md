```mermaid
classDiagram
    class Program {
        +Main(args: string[]) static$
    }

    class GameManager {
        +GameManager(uiFactory: IUserInterfaceFactory)
        +ProcessAttempt(inputData: IUserInterface, gameSetting: GameSetting, previousGameState: GameState) GameState$ 
    }

    class GameSetting {
        +int SecretNumber
        +int MaxAttempts
    }

    class GameState {
        +int? LastInputNumber
        +int CurrentAttempt
        +bool IsSuccess
        +UpdateState(input: int, gameState: GameState, gameSetting: GameSetting) GameState$
    }

    class UserInterfaceHelper {
        +GetUser() string$
        +InputTime() DateTime$
        +IsValidInput(input: string?, result: out int) bool$
    }

    class IUserInterface {
        <<interface>>
        +GetUser() string
        +InputInteger() int
        +InputTime() DateTime
        +StandardOutput(output: string) void
    }

    class IUserInterfaceFactory {
        <<interface>>
        +CreateUserInterface(config: UserInterfaceType) IUserInterface
    }

    class UserInterfaceFactory {
        +CreateUserInterface(config: UserInterfaceType) IUserInterface
    }

    class CliIo {
        +GetUser() string
        +InputInteger() int
        +InputTime() DateTime
        +StandardOutput(output: string) void
    }

    class FileIo {
        +FilePath string
        +GetUser() string
        +InputInteger() int
        +InputTime() DateTime
        +StandardOutput(output: string) void
    }

    Program ..> GameManager : creates
    Program ..> UserInterfaceFactory : creates
    GameManager ..> GameState : uses
    GameManager ..> GameSetting : uses
    GameManager --> IUserInterface : uses
    GameManager --> IUserInterfaceFactory : depends
    UserInterfaceFactory ..|> IUserInterfaceFactory : implements
    CliIo ..|> IUserInterface : implements
    FileIo ..|> IUserInterface : implements
    CliIo ..> UserInterfaceHelper : uses
    FileIo ..> UserInterfaceHelper : uses
    UserInterfaceFactory ..> CliIo : creates
    UserInterfaceFactory ..> FileIo : creates