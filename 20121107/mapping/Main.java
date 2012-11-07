
public class Main
{
	static { System.loadLibrary( "native" ); }

	public native void printHelloWorld();
	public native String getHelloWorld();

	public static void main(String[] arg)
	{
		Main m = new Main();

		m.printHelloWorld();
		System.out.println( "[Java] " + m.getHelloWorld());
	}
}
