
public class Marine extends Unit 
{

	public Marine()
	{
		name = "Marine";
		HP = 100 ;
		sheild = 100;
		level = 1;
	}

	public void attack()
	{
		System.out.println(name +" :Dududududu... ");
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
