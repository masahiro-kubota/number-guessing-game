using Core;
namespace Service {
    public interface IUserInterface {
       string GetUser();
       int InputInteger();
       DateTime InputTime();
       void StandardOutput(string output);
    }
}
