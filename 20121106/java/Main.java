
public class Main
{
	public static void main(String[] args)
	{
		Person p = new Person("Henry",29);
		p.show();

		Person p1 = new Person();
		p1.show();
		
		Car c = new Car("i30",4,"White");
		c.show();
		Car c1 = new Car();
		c1.show();
	}
}
