public class Person {
  private string name;
  private int age;

  public string Name {
    get { return name; }
    set { name = value; }
  }

  public int Age{
    get { return age; }
    set { age = value; }
  }

  public Person(string name, int age) {
    this.name = name;
    this.age = age;
  }

  public void Greet() {
    Console.WriteLine($"Hello {name}");
  }
}

class Program {
  static void Main(string[] args) {
    Console.WriteLine("Hello world!");
    Person person = new Person("Bob", 20);
    person.Greet();
  }
}
