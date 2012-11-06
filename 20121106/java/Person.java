
public class Person
{
	private  String name;
	private int age;

	public Person()
	{
		name = "Henry";
		age = 39;
	}

	public Person(String name, int age)
	{
		this.name = name;
		this.age = age;
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	public void setAge(int age)
	{
		this.age = age;
	}

	public void show()
	{
		System.out.println("name = " + name);
		System.out.println("age = " + age);

	}



}
