
public class Main
{
	public static void main(String arg[])
	{
		Marine marine = new Marine();
		Medic medic = new Medic();
		Ghost ghost = new Ghost();


		Runable[] group = new Runable[10];
		group[0] = marine;
		group[1] = medic;
		group[2] = ghost;

		for(int i = 0; i < 3; i++) 
		{
			group[i].run();
		}
	}
}
