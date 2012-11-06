
public class Bank
{
	public static void main(String[] args)
	{
		Counter c1 = new Counter();
		Counter c2 = new Counter();

		c1.count();
		c1.count();
		c1.count();

		c2.count();
		c2.count();
		c2.count();
		c2.count();

		System.out.println("count : " + c1.cnt);
		System.out.println("count : " + c2.cnt);
	}
}
