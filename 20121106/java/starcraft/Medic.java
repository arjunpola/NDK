
public class Medic extends Unit 
{

	public Medic()
	{
		name = "Medic";
		HP = 100 ;
		sheild = 100;
		level = 1;
	}

	public void repair()
	{
		System.out.println(name +" : healing ");
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
