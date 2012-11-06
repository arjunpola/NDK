
public class Main
{
	public static void main(String arg[])
	{
		Marine marine = new Marine();
		Medic medic = new Medic();
		Ghost ghost = new Ghost();

		marine.attack();
		marine.run();
		marine.stop();

		medic.repair();
		medic.stop();
		medic.run();

		ghost.attack();
		ghost.stop();
		ghost.run();
	}
}
