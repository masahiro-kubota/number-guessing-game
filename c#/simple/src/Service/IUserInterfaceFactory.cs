using Core;
namespace Service {
    public interface IUserInterfaceFactory {
       IUserInterface CreateUserInterface(UserInterfaceType config);
    }
    public enum UserInterfaceType
    {
        File,
        CLI
    }
}
