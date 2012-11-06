
public class Ghost extends Unit 
{

	public Ghost()
	{
		name = "Ghost";
		HP = 100 ;
		sheild = 100;
		level = 1;
	}

	public void attack()
	{
		System.out.println(name +" :Pang ");
	}

	public void stop()
	{
		System.out.println(name +" :Stop!");
	}

	public void run()
	{
		System.out.println(name +"GoGoGo!");
	}


}
